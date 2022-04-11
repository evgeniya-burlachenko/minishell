/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _unset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:35:17 by zcris             #+#    #+#             */
/*   Updated: 2021/12/19 11:17:54 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtins_unset_remove(t_z_array *envp, char *str)
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

static int	builtins_unset_validate(char *str, int *e)
{
	if (str[0] == '-')
	{
		utls_print_errno("unset", str, ERRORS_NOT_OPTION);
		*e = 2;
		return (*e);
	}
	if (utls_keys_validate(str))
	{
		utls_print_errno("unset", str, ERRORS_N_IDENTIFIER);
		*e = 1;
		return (*e);
	}	
	return (0);
}

int	builtins_unset(t_z_array *argv, t_z_array *envp)
{
	size_t	i;
	int		error;
	int		e;

	error = 0;
	e = 0;
	utls_export_setvar("_", (*argv).elem[(*argv).size - 1], envp);
	if ((*argv).size == 0)
		return (0);
	i = 1;
	while (i < (*argv).size)
	{
		if (builtins_unset_validate((*argv).elem[i], &e) == 0)
			builtins_unset_remove(envp, (*argv).elem[i]);
		else
			error = e;
		i++;
	}
	return (error);
}
