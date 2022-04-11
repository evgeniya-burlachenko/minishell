/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_ft_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 08:27:31 by zcris             #+#    #+#             */
/*   Updated: 2021/12/29 09:40:47 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	utls_ft_is_space(char c)
{
	if (c == '\t' || \
		c == '\n' || \
		c == '\v' || \
		c == '\f' || \
		c == '\r' || \
		c == ' ')
	{
		return (1);
	}
	return (0);
}

int	utls_ft_ifkey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

void	ft_clean(char *ptr)
{
	if (ptr != NULL)
		free(ptr);
	ptr = NULL;
}

int	is_control_char(char c)
{
	static char	*temp = "~\"'$<>";
	int			i;

	i = -1;
	while (temp[++i])
	{
		if (temp[i] == c)
			return (1);
	}
	return (0);
}

char	*ft_join_or_dup(char *start, char *end)
{
	if (ft_strlen(end) == 0)
		return (ft_strdup(start));
	return (ft_strjoin(start, end));
}
