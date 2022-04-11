/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:34:20 by zcris             #+#    #+#             */
/*   Updated: 2021/12/29 09:51:33 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_errors_fork(void)
{
	utls_print_error(ERRORS_FORK);
	exit(1);
}

void	fork_errors_waitpid(void)
{
	utls_print_error(ERRORS_WAITPID);
	exit(1);
}

void	fork_errors_pipe(void)
{
	utls_print_error(ERRORS_WAITPID);
	exit(1);
}
