/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _quote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:04:30 by skelly            #+#    #+#             */
/*   Updated: 2021/12/29 08:07:21 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_gap(char *str, int *i)
{
	int		j;
	char	*tmp_start;
	char	*tmp_inside;
	char	*tmp_finish;

	j = *i;
	while (str[++(*i)])
		if (str[*i] == '\'')
			break ;
	tmp_start = ft_substr(str, 0, j);
	tmp_inside = ft_substr(str, j + 1, *i - j - 1);
	tmp_finish = ft_strdup(str + *i + 1);
	utls_ft_set(&tmp_start, utls_parser_str3join(tmp_start, \
	tmp_inside, tmp_finish));
	utls_ft_4free(tmp_inside, tmp_finish, NULL, NULL);
	*i -= 2;
	return (tmp_start);
}

char	*ft_gap2(char *str, int *i, t_z_array *env)
{
	int		j;
	char	*tmp_s;
	char	*tmp_inside;
	char	*tmp_finish;
	int		k;

	k = -1;
	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '\"')
			break ;
	}
	tmp_s = ft_substr(str, 0, j);
	tmp_inside = ft_substr(str, j + 1, *i - j - 1);
	while (tmp_inside[++k])
	{
		if (tmp_inside[k] == '$')
			utls_ft_set(&tmp_inside, ft_dollar(tmp_inside, &k, env, 1));
	}
	tmp_finish = ft_strdup(str + *i + 1);
	*i = ft_strlen(tmp_s) + ft_strlen(tmp_inside) - 1;
	utls_ft_set(&tmp_s, utls_parser_str3join(tmp_s, tmp_inside, tmp_finish));
	utls_ft_4free(tmp_inside, tmp_finish, NULL, NULL);
	return (tmp_s);
}
