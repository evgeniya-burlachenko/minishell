/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 06:57:16 by zcris             #+#    #+#             */
/*   Updated: 2021/12/29 14:14:22 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_and_run_command(t_z_array *params, t_z_array *env)
{
	char	*command;

	if ((*params).size == 0)
		return (0);
	command = (*params).elem[0];
	if (utls_ft_strcmp(command, "cd") == 0)
		return (builtins_cd(params, env));
	else if (utls_ft_strcmp(command, "echo") == 0)
		return (builtins_echo(params, env));
	else if (utls_ft_strcmp(command, "env") == 0)
		return (builtins_env(params, env));
	else if (utls_ft_strcmp(command, "exit") == 0)
		return (builtins_exit(params, env));
	else if (utls_ft_strcmp(command, "export") == 0)
	{
		utls_export_set_underscore(params, env);
		return (builtins_export(params, env));
	}
	else if (utls_ft_strcmp(command, "pwd") == 0)
		return (builtins_pwd(params, env));
	else if (utls_ft_strcmp(command, "unset") == 0)
		return (builtins_unset(params, env));
	else
		return (try_to_execve(params, env));
}

static int	get_redirects(t_z_array *params, t_z_array *redic)
{
	int	i;

	i = -1;
	if ((int)params->size == 1 && utls_redirect_is_ctrl_sqnce(params->elem[0]))
	{
		utls_print_errno(ERRORS_NOT_TOKEN, params->elem[i + 1], NULL);
		return (258);
	}
	while (++i < (int)params->size - 1)
	{
		if (utls_redirect_is_ctrl_sqnce(params->elem[i]))
		{
			if (utls_redirect_is_ctrl_sqnce(params->elem[i + 1]))
			{
				utls_print_errno(ERRORS_NOT_TOKEN, params->elem[i + 1], NULL);
				return (258);
			}
			z_array_append(redic, params->elem[i]);
			z_array_append(redic, params->elem[i + 1]);
			z_array_remove(params, i + 1);
			z_array_remove(params, i);
			i--;
		}
	}
	return (0);
}

static int	apply_redirects_and_run(t_z_array *params, t_z_array *envir)
{
	t_z_array	redic;
	int			fd[2];
	int			status;

	fd[0] = -1;
	fd[1] = -1;
	status = 0;
	z_array_init(&redic);
	status = get_redirects(params, &redic);
	if (status)
		return (status);
	status = utls_redirect_open_files(&redic, &fd[0], &fd[1]);
	if (status == 0)
	{
		utls_redirect_set_fd(fd[0], fd[1], 1);
		utls_redirect_close_files(&fd[0], &fd[1]);
		status = find_and_run_command(params, envir);
		utls_redirect_set_fd(fd[0], fd[1], 0);
	}
	z_array_free(&redic);
	return (status);
}

static int	change_and_run(t_z_array *p, t_z_array *e, int f1, int f0)
{
	int	status;

	status = 0;
	utls_redirect_dup2_and_close(f1, STDOUT_FILENO);
	status = apply_redirects_and_run(p, e);
	utls_redirect_dup2_and_close(f0, STDIN_FILENO);
	return (status);
}

int	runner(char *read_buff, t_z_array *params, t_z_array *envir)
{
	char		*ostatok;
	int			status;
	int			fd_back[2];
	int			fd[2];

	status = ft_preparser(read_buff);
	if (status != 0)
		return (status);
	utls_redirect_dup_std_backup(&fd_back[0], &fd_back[1]);
	status = 0;
	ostatok = ft_strdup(read_buff);
	while (ostatok)
	{
		utls_ft_set(&ostatok, parser(ostatok, params, envir));
		if (ostatok)
		{
			pipe(fd);
			status = change_and_run(params, envir, fd[1], fd[0]);
		}
		if (!ostatok)
			status = change_and_run(params, envir, fd_back[1], fd_back[0]);
		z_array_re_init(params);
	}
	ft_clean(ostatok);
	return (status);
}
