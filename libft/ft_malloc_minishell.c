/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_minishell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 08:52:02 by zcris             #+#    #+#             */
/*   Updated: 2021/12/28 09:23:13 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	utls_print_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	*utls_ft_alloc(size_t size)
{
	void	*res;

	res = (void *)malloc(size);
	if (!res)
	{
		utls_print_error(ERRORS_MALLOK);
		exit (12);
	}
	return ((void *)res);
}
