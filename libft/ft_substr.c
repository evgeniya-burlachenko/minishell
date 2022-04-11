/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:44:58 by skelly            #+#    #+#             */
/*   Updated: 2021/12/05 07:18:02 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*res;
	size_t		j;
	size_t		i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	if (i < start)
		len = 0;
	else if (i < start + len)
		len = i - start;
	j = 0;
	res = (char *)utls_ft_alloc(len + 1);
	if (!res)
		return (0);
	while (j < len && start <= i)
		res[j++] = s[start++];
	res[j] = '\0';
	return (res);
}
