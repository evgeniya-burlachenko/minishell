/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:44:48 by skelly            #+#    #+#             */
/*   Updated: 2021/12/04 15:44:49 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;
	char		*dst;

	i = 0;
	dst = (char *)haystack;
	if (*needle == 0)
		return (dst);
	while (dst[i] && i < len)
	{
		j = 0;
		if (dst[i] == needle[j])
		{
			while (i + j < len && dst[i + j] == needle[j])
			{
				j++;
				if (!needle[j])
					return (dst + i);
			}
		}
		i++;
	}
	return (0);
}
