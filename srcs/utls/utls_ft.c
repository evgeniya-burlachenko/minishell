/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 08:38:39 by zcris             #+#    #+#             */
/*   Updated: 2021/12/29 09:40:43 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	utls_ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*s1_1;
	unsigned char	*s2_2;

	s1_1 = (unsigned char *)s1;
	s2_2 = (unsigned char *)s2;
	while ((*s1_1 || *s2_2))
	{
		if (*s1_1++ != *s2_2++)
			return (*(s1_1 - 1) - *(s2_2 - 1));
	}
	return (0);
}

void	utls_ft_free_split_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
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

void	utls_ft_memset(char **str, char c)
{
	size_t	i;

	i = 0;
	while ((*str)[i])
	{
		(*str)[i] = c;
		i++;
	}
}

char	*ft_strrchr_2(const char *s, int c)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = ft_strlen(str);
	if ((char)c == 0)
		return (str + i);
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}
