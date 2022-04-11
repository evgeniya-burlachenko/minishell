/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:33:51 by zcris             #+#    #+#             */
/*   Updated: 2021/12/24 09:29:17 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtins_export_print_env_item(char *str, t_z_array *envp)
{
	char	*tmp;
	char	*tmp_val;

	if (NULL == ft_strrchr(str, '='))
		printf("declare -x %s\n", str);
	else
	{
		tmp = utls_keys_get(str);
		if (NULL == tmp)
			return (1);
		tmp_val = utls_keys_value_get(tmp, envp);
		if (NULL == tmp_val)
			printf("declare -x %s=\"\"\n", tmp);
		else
		{
			printf("declare -x %s=\"%s\"\n", tmp, tmp_val);
			free(tmp_val);
		}
		free(tmp);
	}
	return (0);
}

static int	builtins_export_print_env(t_z_array *envp)
{
	int		i;

	i = -1;
	z_array_sort(envp, utls_ft_strcmp);
	while (++i < (int)(*envp).size)
	{
		if (builtins_export_print_env_item((*envp).elem[i], envp))
			return (1);
	}
	return (0);
}

static int	builtins_export_change(t_z_array *envp, char *s)
{
	char	*tmp;
	int		plus;
	char	*old_v;
	char	*str;

	tmp = utls_keys_get(s);
	if (NULL == tmp)
		return (utls_print_e_return("export", s, ERRORS_N_IDENTIFIER, 1));
	utls_export_is_plus(&tmp, &plus);
	if (utls_keys_validate(tmp))
	{
		free(tmp);
		return (utls_print_e_return("export", s, ERRORS_N_IDENTIFIER, 1));
	}
	str = ft_strdup(s);
	old_v = utls_keys_value_get(tmp, envp);
	if (plus)
	{
		utls_ft_set(&old_v, ft_strjoin(old_v, (ft_strrchr(str, '=')) + 1));
		utls_ft_set(&str, utls_keys_create_string(tmp, old_v));
	}
	utls_export_remove_old(envp, tmp);
	z_array_append(envp, str);
	utls_ft_4free(old_v, tmp, str, NULL);
	return (0);
}

int	builtins_export(t_z_array *argv, t_z_array *envp)
{
	size_t	i;
	int		error;
	int		e;

	error = 0;
	e = 0;
	if ((*argv).size == 1)
		return (builtins_export_print_env(envp));
	i = 1;
	while (i < (*argv).size)
	{
		if ((*argv).elem[i][0] == '-')
		{
			utls_print_errno("export", (*argv).elem[i], ERRORS_NOT_OPTION);
			error = 2;
		}
		else
			e = builtins_export_change(envp, (*argv).elem[i]);
		if (e != 0)
			error = e;
		i++;
	}
	return (error);
}
