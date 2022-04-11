/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_ft_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:29:06 by zcris             #+#    #+#             */
/*   Updated: 2021/12/29 14:15:20 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr_or_empty(char *str, int start_index, int count)
{
	char	*result;

	result = NULL;
	if (ft_strlen(str) != 0)
		result = ft_substr(str, start_index, count);
	else
		result = ft_calloc(1, sizeof(char));
	return (result);
}
