/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tilda_red2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 16:59:26 by skelly            #+#    #+#             */
/*   Updated: 2021/12/29 08:02:44 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_main_redic(char *str, int *i, int j, t_z_array *p)
{
	char			*tmp_finish;
	char			*tmp_redir;

	tmp_redir = ft_substr(str, j, 2);
	*i = j + ft_strlen(tmp_redir) - 2;
	utls_ft_set(&tmp_redir, utls_strtrim_symb(tmp_redir));
	z_array_append(p, tmp_redir);
	ft_clean(tmp_redir);
	tmp_finish = ft_strdup(str + j + 2);
	if (tmp_finish[0] == ' ' && tmp_finish[(ft_strlen(tmp_finish) - 1)] == ' ')
	{
		*i = j + 1;
		utls_ft_set(&tmp_finish, utls_strtrim_symb(tmp_finish));
	}
	if (tmp_finish[0] == ' ' || tmp_finish[(ft_strlen(tmp_finish) - 1)] == ' ')
	{
		*i = j - 1;
		utls_ft_set(&tmp_finish, utls_strtrim_symb(tmp_finish));
	}
	return (tmp_finish);
}

static void	offset_i(char *result, int *i)
{
	int	k;

	k = -1;
	while (result[++(k)])
	{
		if (result[k] == '$')
			*i = *i + 1;
	}
}

char	*ft_redic2(char *str, int *i, t_z_array *params)
{
	int		j;
	int		k;
	char	*result;

	k = -1;
	j = *i;
	while (str[++(*i)])
		;
	if (j != 0)
	{
		result = ft_substr(str, 0, j);
		*i = j + ft_strlen(result) - 1;
		utls_ft_set(&result, utls_strtrim_symb(result));
		z_array_append(params, result);
		utls_ft_set(&result, ft_main_redic(str, i, j, params));
		*i = j - 3;
		return (result);
	}
	result = ft_main_redic(str, i, j, params);
	*i = j - 1;
	offset_i(result, i);
	return (result);
}
