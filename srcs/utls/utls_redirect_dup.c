/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_redirect_dup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 10:31:31 by zcris             #+#    #+#             */
/*   Updated: 2021/12/28 08:16:27 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	utls_redirect_dup2(int a, int b)
{
	int	result;

	result = dup2(a, b);
	if (result == -1)
	{
		utls_print_error(ERRORS_DUB2);
		exit (1);
	}
}

int	utls_redirect_dup(int a)
{
	int	result;

	result = dup(a);
	if (result == -1)
	{
		utls_print_error(ERRORS_DUB);
		exit (1);
	}
	return (result);
}

void	utls_redirect_dup2_and_close(int a, int b)
{
	int	result;

	result = dup2(a, b);
	if (result == -1)
	{
		utls_print_error(ERRORS_DUB2);
		exit (1);
	}
	close(a);
}

void	utls_redirect_dup_std_backup(int *f0, int *f1)
{
	*f0 = utls_redirect_dup(STDIN_FILENO);
	*f1 = utls_redirect_dup(STDOUT_FILENO);
}
