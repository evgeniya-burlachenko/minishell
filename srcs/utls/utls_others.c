/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_others.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:51:38 by zcris             #+#    #+#             */
/*   Updated: 2021/12/26 08:38:47 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	utls_others_is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

int	utls_others_error_handling(int status, char *str)
{
	if (WTERMSIG(status))
	{
		printf("\n");
		if (WTERMSIG(status) == 3)
			utls_print_error("\033[1A^\\Quit: 3\n");
		if (WTERMSIG(status) == 2)
			return (130);
		else
			return (128 + WEXITSTATUS(status));
	}
	if (WIFEXITED(status) == 0 && WEXITSTATUS(status) > 1)
		status = utls_print_bash_errors(str, status);
	return (WEXITSTATUS(status));
}

int	utls_others_is_whith_path(char *command)
{
	return (ft_strncmp(command, "./", 2) == 0 || \
	command[0] == '/' || ft_strncmp(command, "../", 3) == 0);
}
