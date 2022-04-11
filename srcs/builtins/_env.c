/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:30:39 by zcris             #+#    #+#             */
/*   Updated: 2021/12/19 11:17:54 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins_env(t_z_array *argv, t_z_array *envp)
{
	size_t	i;

	(void)argv;
	utls_export_setvar("_", "env", envp);
	i = 0;
	while (i < (*envp).size)
	{
		if (ft_strrchr((*envp).elem[i], '='))
			printf("%s\n", (*envp).elem[i]);
		i++;
	}
	return (0);
}
