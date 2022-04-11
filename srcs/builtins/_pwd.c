/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _pwd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:34:24 by zcris             #+#    #+#             */
/*   Updated: 2021/12/19 11:17:54 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins_pwd(t_z_array *argv, t_z_array *envp)
{
	char	*path;

	utls_export_setvar("_", (*argv).elem[(*argv).size - 1], envp);
	path = getcwd(NULL, 0);
	if (NULL == path)
		return (errno);
	printf("%s\n", path);
	free(path);
	return (0);
}
