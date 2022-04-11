/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 06:34:10 by zcris             #+#    #+#             */
/*   Updated: 2021/12/19 11:17:54 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*utls_keys_get(char *str)
{
	char	*pos;
	char	*result;

	if (!(ft_strlen(str) > 0))
		return (NULL);
	pos = ft_strrchr_2(str, '=');
	if (pos == str)
		return (NULL);
	if (NULL == pos)
		result = ft_strdup(str);
	else
		result = ft_substr(str, 0, pos - str);
	return (result);
}

char	*utls_keys_value_get(char *key, t_z_array *envp)
{
	size_t	i;
	size_t	len;
	char	*result;

	len = ft_strlen(key);
	if (!(len > 0))
		return (NULL);
	i = 0;
	while (i < (*envp).size)
	{
		if (ft_strncmp(key, (*envp).elem[i], len) == 0)
		{
			if (*((*envp).elem[i] + len) == '=')
			{
				result = ft_strdup((*envp).elem[i] + len + 1);
				return (result);
			}
			else if (len == ft_strlen((*envp).elem[i]))
				return (NULL);
		}
		i++;
	}
	return (NULL);
}

int	utls_keys_validate(char *key)
{
	size_t	i;

	if (NULL == key || ft_strlen(key) == 0)
		return (1);
	if (!(key[0] == '_' || ft_isalpha(key[0])))
		return (1);
	i = 0;
	while (key[i])
	{
		if (!(key[i] == '_' || ft_isalnum(key[i])))
			return (1);
		i++;
	}
	return (0);
}

char	*utls_keys_create_string(char *key, char *value)
{
	char	*tmp0;
	char	*result;

	tmp0 = ft_strjoin(key, "=");
	result = ft_strjoin(tmp0, value);
	free(tmp0);
	return (result);
}

int	utls_keys_pipestatus(int status, t_z_array *envp)
{
	t_z_array	tmp;
	char		*value_to_string;
	char		*key_value;

	z_array_init(&tmp);
	value_to_string = ft_itoa(status);
	key_value = utls_keys_create_string(PIPESTATUS, value_to_string);
	z_array_append(&tmp, "export");
	z_array_append(&tmp, key_value);
	free(value_to_string);
	free(key_value);
	builtins_export(&tmp, envp);
	z_array_free(&tmp);
	return (0);
}
