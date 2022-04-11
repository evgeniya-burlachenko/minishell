/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:25:41 by skelly            #+#    #+#             */
/*   Updated: 2021/12/29 15:02:29 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_envr(t_z_array *envir, char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		z_array_append(envir, envp[i]);
		i++;
	}
}

static int	set_enviroment_on_start(t_z_array *envir)
{
	int		lvl;
	char	*tmp;

	utls_keys_pipestatus(0, envir);
	tmp = utls_keys_value_get("SHLVL", envir);
	lvl = 0;
	if (NULL != tmp)
	{
		lvl = ft_atoi(tmp);
		free(tmp);
	}
	tmp = ft_itoa((lvl + 1));
	utls_export_setvar("SHLVL", tmp, envir);
	free(tmp);
	utls_export_set_only_key("OLDPWD", envir);
	return (0);
}

static void	minishell(t_z_array *params, t_z_array *envir)
{
	char		*read_buff;
	int			status;

	while (1)
	{
		read_buff = readline(PROMPT);
		if (NULL == read_buff)
		{
			utls_print_error(PROMPTEXIT);
			break ;
		}
		if (ft_strlen(read_buff) > 0)
		{
			add_history(read_buff);
			status = runner(read_buff, params, envir);
			utls_keys_pipestatus(status, envir);
		}
		free(read_buff);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_z_array	params;
	t_z_array	envir;

	(void)argv;
	if (argc != 1)
	{
		utls_print_error(ERRORS_SHELL_PARAMS);
		return (0);
	}
	z_array_init(&params);
	z_array_init(&envir);
	copy_envr(&envir, envp);
	set_enviroment_on_start(&envir);
	signals_init();
	rl_catch_signals = 0;
	minishell(&params, &envir);
	z_array_free(&params);
	z_array_free(&envir);
	return (0);
}
