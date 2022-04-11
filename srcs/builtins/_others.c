/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _others.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 06:45:28 by zcris             #+#    #+#             */
/*   Updated: 2021/12/28 12:55:19 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path_env(char *command, t_z_array *env, int *err)
{
	char	**allpathes;
	char	*result;
	int		i;

	result = utls_keys_value_get("PATH", env);
	allpathes = ft_split(result, ':');
	free(result);
	if (NULL == allpathes)
		return (NULL);
	i = -1;
	while (allpathes[++i])
	{
		result = ft_strjoin(allpathes[i], command);
		if (access(result, F_OK) == 0)
		{
			utls_ft_free_split_array(allpathes);
			return (result);
		}
		*err = errno;
		free(result);
	}
	utls_ft_free_split_array(allpathes);
	return (NULL);
}

static char	*get_path(t_z_array *params, t_z_array *env, int *err)
{
	char	*tmp;
	char	*result;

	if (utls_others_is_whith_path((*params).elem[0]))
	{
		if (access((*params).elem[0], F_OK) == 0)
			return (ft_strdup((*params).elem[0]));
		else
			*err = errno;
		return (NULL);
	}
	else
	{
		tmp = ft_strjoin("/", (*params).elem[0]);
		result = get_path_env(tmp, env, err);
		free (tmp);
		if (NULL == result)
		{
			*err = 127;
		}
		return (result);
	}
	return (NULL);
}

static int	child_routine(t_z_array *params, t_z_array *env)
{
	char	*command;
	int		err;

	err = 0;
	command = get_path(params, env, &err);
	z_array_null_terminate(params);
	z_array_null_terminate(env);
	if (execve(command, (*params).elem, (*env).elem) == -1)
		err = errno;
	free(command);
	return (err);
}

static int	is_command_exist(t_z_array *params, t_z_array *env)
{
	char	*command;
	int		err;

	err = 0;
	command = NULL;
	command = get_path(params, env, &err);
	if (NULL == command)
		return (err);
	if (utls_others_is_directory(command))
	{
		free(command);
		return (126);
	}
	free(command);
	return (0);
}

int	try_to_execve(t_z_array *params, t_z_array *env)
{
	pid_t	pid;
	int		status;

	status = is_command_exist(params, env);
	if (status != 0)
	{
		status = utls_print_bash_errors(params->elem[0], status << 8);
		return (status);
	}
	pid = fork();
	if (pid < 0)
		fork_errors_fork();
	if (pid == 0)
	{
		signals_reset();
		status = child_routine(params, env);
		exit (status);
	}
	signals_pause();
	if (waitpid(pid, &status, WUNTRACED) < 0)
		fork_errors_waitpid();
	signals_init();
	return (utls_others_error_handling(status, (*params).elem[0]));
}
