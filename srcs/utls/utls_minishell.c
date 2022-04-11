/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 10:04:25 by zcris             #+#    #+#             */
/*   Updated: 2021/12/24 10:18:49 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	utls_ft_set(char **str, char *new_value)
{
	free(*str);
	*str = NULL;
	*str = new_value;
}

static void	utls_ft_free_if_not_null(void *p)
{
	if (NULL != p)
	{
		free(p);
		p = NULL;
	}
}

void	utls_ft_4free(void *p1, void *p2, void *p3, void *p4)
{
	utls_ft_free_if_not_null(p1);
	utls_ft_free_if_not_null(p2);
	utls_ft_free_if_not_null(p3);
	utls_ft_free_if_not_null(p4);
}
