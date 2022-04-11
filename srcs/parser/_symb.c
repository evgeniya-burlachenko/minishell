/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _symb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 11:27:23 by skelly            #+#    #+#             */
/*   Updated: 2021/12/29 09:29:35 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_start_finish(char *str, int *i, int j)
{
	char	*tmp_start;
	char	*tmp_finish;

	tmp_start = ft_substr(str, 0, j);
	tmp_finish = ft_strdup(str + *i + 2);
	tmp_start = ft_strjoin(tmp_start, tmp_finish);
	ft_clean(tmp_finish);
	return (tmp_start);
}

char	*ft_dollar(char *str, int *i, t_z_array *env, int is_qu)
{
	char	*tmp_finish;
	char	*tmp_start;
	int		size;
	int		nl;

	nl = 0;
	tmp_start = set_env_inside_string(str, env, i, &nl);
	size = ft_strlen(tmp_start);
	while (!is_qu && utls_ft_is_space(str[*i]) && nl == 1)
		(*i)++;
	tmp_finish = ft_strdup(str + *i);
	*i = ft_strlen(tmp_start) - 1;
	if (size > 0)
		if (tmp_start[size - 1] == '"' || tmp_start[size - 1] == '\'')
			(*i)--;
	utls_ft_set(&tmp_start, ft_strjoin(tmp_start, tmp_finish));
	ft_clean(tmp_finish);
	return (tmp_start);
}
