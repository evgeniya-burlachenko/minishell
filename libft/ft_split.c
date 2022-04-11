/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:44:20 by skelly            #+#    #+#             */
/*   Updated: 2021/12/11 09:46:48 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int		i;
	int		words;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static void	*ft_clean_split(char **res, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

static char	*new_word(const char *s, size_t n)
{
	char	*str;

	str = utls_ft_alloc(sizeof(char) * n + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, n + 1);
	return (str);
}

char	**ft_split(char	const *s, char c)
{
	int		i;
	int		j;
	int		word;
	char	**res;

	i = 0;
	word = 0;
	if (!s)
		return (NULL);
	res = (char **)utls_ft_alloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!res)
		return (ft_clean_split(res, i));
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
			res[word++] = new_word(s + j, i - j);
	}
	res[word] = NULL;
	return (res);
}
