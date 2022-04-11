/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:44:40 by zcris             #+#    #+#             */
/*   Updated: 2021/12/27 10:12:25 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	utls_redirect_set_fd(int i, int o, int set_reset)
{
	static int	backup_fd[2];
	static int	first;

	if (first == 0)
	{
		backup_fd[0] = utls_redirect_dup(STDIN_FILENO);
		backup_fd[1] = utls_redirect_dup(STDOUT_FILENO);
		first = 1;
	}
	if (set_reset == 1)
	{
		if (i > 0)
			utls_redirect_dup2(i, STDIN_FILENO);
		if (o > 0)
			utls_redirect_dup2(o, STDOUT_FILENO);
		return ;
	}
	utls_redirect_dup2(backup_fd[0], STDIN_FILENO);
	utls_redirect_dup2(backup_fd[1], STDOUT_FILENO);
	utls_redirect_close_files(&backup_fd[0], &backup_fd[1]);
	first = 0;
}

int	utls_redirect_open_files(t_z_array *redic, int *i, int *o)
{
	int	j;

	j = -1;
	while (++j < (int)redic->size - 1)
	{
		if (utls_ft_strcmp(redic->elem[j], ">") == 0)
		{
			if (utls_redirect_files_o(i, o, redic->elem[++j]))
				return (1);
		}
		else if (utls_ft_strcmp(redic->elem[j], ">>") == 0)
		{
			if (utls_redirect_files_oapp(i, o, redic->elem[++j]))
				return (1);
		}
		else if (utls_ft_strcmp(redic->elem[j], "<") == 0)
		{
			if (utls_redirect_files_i(i, o, redic->elem[++j]))
				return (1);
		}
		else if (utls_ft_strcmp(redic->elem[j], "<<") == 0)
			ft_heredoc(i, redic->elem[j + 1]);
	}
	return (0);
}

void	utls_redirect_close_files(int *i, int *o)
{
	if (*i != -1)
	{
		close(*i);
		*i = -1;
	}
	if (*o != -1)
	{
		close(*o);
		*o = -1;
	}
}

int	utls_redirect_is_ctrl_sqnce(char *str)
{
	if (utls_ft_strcmp(str, ">") == 0 || \
		utls_ft_strcmp(str, ">>") == 0 || \
		utls_ft_strcmp(str, "<") == 0 || \
		utls_ft_strcmp(str, "<<") == 0)
	{
		return (1);
	}
	return (0);
}
