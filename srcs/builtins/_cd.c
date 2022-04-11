/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:28:18 by zcris             #+#    #+#             */
/*   Updated: 2021/12/29 10:55:42 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	builtins_cd_set_env(char *old_pwd, char *dir, t_z_array *envp)
{
	t_z_array	tmp;
	char		*dir_str;
	char		*old_pwd_str;

	dir_str = ft_strjoin("PWD=", dir);
	old_pwd_str = ft_strjoin("OLDPWD=", old_pwd);
	z_array_init(&tmp);
	z_array_append(&tmp, "export");
	z_array_append(&tmp, dir_str);
	z_array_append(&tmp, old_pwd_str);
	builtins_export(&tmp, envp);
	utls_ft_4free(dir_str, old_pwd_str, NULL, NULL);
	z_array_free(&tmp);
}

static int	is_dir_home_null(char *dir_home)
{
	if (NULL == dir_home)
	{
		utls_print_errno("cd", NULL, ERRORS_NOT_HOME);
		return (1);
	}
	else
		return (0);
}

static char	*get_path(t_z_array *argv, t_z_array *envp)
{
	char	*dir_home;
	char	*dir;

	dir_home = utls_keys_value_get("HOME", envp);
	if ((*argv).size == 1)
	{
		if (is_dir_home_null(dir_home))
			return (NULL);
		else
			return (dir_home);
	}
	else if (*((*argv).elem[1]) == '~')
	{
		if (is_dir_home_null(dir_home))
			return (NULL);
		dir = ft_strjoin(dir_home, (*argv).elem[1] + 1);
	}
	else
		dir = ft_strdup((*argv).elem[1]);
	ft_clean(dir_home);
	return (dir);
}

int	builtins_cd(t_z_array *argv, t_z_array *envp)
{
	char	*dir;
	char	*old_pwd;

	utls_export_setvar("_", (*argv).elem[(*argv).size - 1], envp);
	dir = get_path(argv, envp);
	if (NULL == dir)
		return (1);
	old_pwd = utls_keys_value_get("PWD", envp);
	if (utls_ft_strcmp(dir, old_pwd) == 0)
	{
		utls_ft_4free(dir, old_pwd, NULL, NULL);
		return (0);
	}
	if (chdir(dir) == -1)
	{
		utls_ft_4free(dir, old_pwd, NULL, NULL);
		utls_print_errno("cd", (*argv).elem[1], strerror(errno));
		return (1);
	}
	utls_ft_set(&dir, getcwd(NULL, 0));
	builtins_cd_set_env(old_pwd, dir, envp);
	utls_ft_4free(dir, old_pwd, NULL, NULL);
	return (0);
}
