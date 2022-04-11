/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_print_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 07:28:12 by zcris             #+#    #+#             */
/*   Updated: 2021/12/27 10:17:23 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	utls_print_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	utls_print_errno(char *ref, char *obj, char *subj)
{
	utls_print_error(ERRORS_PROGRAMM);
	if (!(NULL == ref))
	{
		utls_print_error(ref);
		utls_print_error(": ");
	}
	if (!(NULL == obj))
	{
		utls_print_error("`");
		utls_print_error(obj);
		utls_print_error("'");
		if (!(NULL == subj))
			utls_print_error(": ");
	}
	utls_print_error(subj);
	write(2, "\n", 1);
}

int	utls_print_bash_errors(char *str, int status)
{
	if (WEXITSTATUS(status) == 126)
	{
		if (utls_others_is_directory(str))
			utls_print_errno(NULL, str, ERRORS_126_DIR);
		else
			utls_print_errno(NULL, str, ERRORS_126);
	}
	else if (WEXITSTATUS(status) == 2)
	{
		utls_print_errno(NULL, str, ERRORS_2);
		return (127);
	}
	else if (WEXITSTATUS(status) == 127)
		utls_print_errno(NULL, str, ERRORS_127);
	else if (WEXITSTATUS(status) == 128)
		utls_print_errno(NULL, str, ERRORS_128);
	else if (WEXITSTATUS(status) == 130)
		utls_print_errno(NULL, str, ERRORS_130);
	else if (WEXITSTATUS(status) == 255)
		utls_print_errno(NULL, str, ERRORS_255);
	else
		utls_print_errno(NULL, str, strerror(WEXITSTATUS(status)));
	return (status >> 8);
}

int	utls_print_e_return(char *ref, char *obj, char *subj, int code)
{
	utls_print_errno(ref, obj, subj);
	return (code);
}
