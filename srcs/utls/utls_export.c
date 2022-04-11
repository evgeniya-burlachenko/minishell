/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 07:54:27 by zcris             #+#    #+#             */
/*   Updated: 2021/12/29 14:15:10 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	utls_export_is_plus(char **str, int *flag)
{
	size_t	size;

	size = ft_strlen(*str);
	if ((*str)[size - 1] == '+')
	{
		*flag = 1;
		utls_ft_set(str, ft_substr(*str, 0, size - 1));
		return ;
	}
	*flag = 0;
}

int	utls_export_setvar(char *key, char *value, t_z_array *envp)
{
	t_z_array	tmp;
	char		*key_value;

	z_array_init(&tmp);
	key_value = utls_keys_create_string(key, value);
	z_array_append(&tmp, "export");
	z_array_append(&tmp, key_value);
	free(key_value);
	builtins_export(&tmp, envp);
	z_array_free(&tmp);
	return (0);
}

int	utls_export_set_only_key(char *key, t_z_array *envp)
{
	t_z_array	tmp;

	z_array_init(&tmp);
	z_array_append(&tmp, "export");
	z_array_append(&tmp, key);
	builtins_export(&tmp, envp);
	z_array_free(&tmp);
	return (0);
}

int	utls_export_remove_old(t_z_array *envp, char *str)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	while (i < (*envp).size)
	{
		if (ft_strncmp(str, (*envp).elem[i], len) == 0 && \
			(*((*envp).elem[i] + len) == '=' || \
			len == ft_strlen((*envp).elem[i])))
		{
			z_array_remove(envp, i);
			break ;
		}
		i++;
	}
	return (0);
}

void	utls_export_set_underscore(t_z_array *params, t_z_array *env)
{
	char	*tmp;

	tmp = utls_keys_get((*params).elem[(*params).size - 1]);
	utls_export_setvar("_", tmp, env);
	ft_clean(tmp);
}
