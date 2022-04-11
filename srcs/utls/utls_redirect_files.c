/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_redirect_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:05:49 by zcris             #+#    #+#             */
/*   Updated: 2021/12/24 11:23:24 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	utls_redirect_files_o(int *i, int *o, char *f)
{
	if (*o > 0)
		close(*o);
	*o = open(f, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*o < 0)
	{
		utls_print_errno(NULL, f, strerror(errno));
		utls_redirect_close_files(i, o);
		return (1);
	}
	return (0);
}

int	utls_redirect_files_oapp(int *i, int *o, char *f)
{
	if (*o > 0)
		close(*o);
	*o = open(f, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (*o < 0)
	{
		utls_print_errno(NULL, f, strerror(errno));
		utls_redirect_close_files(i, o);
		return (1);
	}
	return (0);
}

int	utls_redirect_files_i(int *i, int *o, char *f)
{
	if (*i > 0)
		close(*i);
	*i = open(f, O_RDONLY, 0644);
	if (*i < 0)
	{
		utls_print_errno(NULL, f, strerror(errno));
		utls_redirect_close_files(i, o);
		return (1);
	}
	return (0);
}
