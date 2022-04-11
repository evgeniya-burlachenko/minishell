/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:27:56 by skelly            #+#    #+#             */
/*   Updated: 2021/12/29 14:15:35 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_gap3(char *str, int *i)
{
	char	*tmp0;

	tmp0 = ft_substr(str, 0, *i);
	while (str[++(*i)] == ' ')
	{
		if (str[*i] == '\0')
			break ;
	}
	(*i)--;
	return (tmp0);
}

static int	control_char_handler(char **str, int *i, t_z_array *e, t_z_array *p)
{
	if ((*str)[*i] == '\"')
	{
		utls_ft_set(str, ft_gap2((*str), i, e));
		if (ft_strlen((*str)) == 0)
			return (1);
	}
	else if ((*str)[*i] == '$')
		utls_ft_set(str, ft_dollar((*str), i, e, 0));
	else if ((*str)[*i] == '~' && *i == 0 && (utls_ft_is_space((*str)[*i + 1]) \
	|| (*str)[*i + 1] == '\0' || (*str)[*i + 1] == '/'))
		utls_ft_set(str, ft_tilda((*str), i, e));
	else if ((*str)[*i] == '\'')
	{
		utls_ft_set(str, ft_gap((*str), i));
		if (ft_strlen((*str)) == 0)
			return (1);
	}
	else if (((*str)[*i + 1] == '>' && (*str)[*i] == '>') \
	|| ((*str)[*i] == '<' && (*str)[*i + 1] == '<'))
		utls_ft_set(str, ft_redic2((*str), i, p));
	else if ((*str)[*i] == '>' || (*str)[*i] == '<')
		utls_ft_set(str, ft_redic1((*str), i, p));
	return (0);
}

static int	parser_routine(char **str, int *j, t_z_array *env, t_z_array *p)
{
	char	*tmp;
	int		i;
	int		emp_q;

	i = *j;
	tmp = NULL;
	while (!((*str)[++i] == 0 || (*str)[i] == '|'))
	{
		if (is_control_char((*str)[i]))
			emp_q = control_char_handler(str, &i, env, p);
		else if (utls_ft_is_space((*str)[i]))
			tmp = ft_gap3((*str), &i);
		if (tmp)
		{
			z_array_append(p, tmp);
			free(tmp);
			tmp = NULL;
			utls_ft_set(str, ft_strdup((*str) + i + 1));
			i = -1;
		}
	}
	*j = i;
	return (emp_q);
}

char	*parser(char *source, t_z_array *p, t_z_array *env)
{
	int		i;
	char	*tmp;
	char	*str;
	int		emp_q;

	emp_q = 0;
	str = ft_strdup(source);
	i = -1;
	utls_ft_set(&str, utls_strtrim_symb(str));
	emp_q = parser_routine(&str, &i, env, p);
	tmp = ft_substr_or_empty(str, 0, i);
	if (ft_strlen(tmp) != 0 || emp_q == 1)
		z_array_append(p, tmp);
	ft_clean(tmp);
	utls_ft_set(&str, ft_strdup(str + i));
	if (ft_strlen(str) == 0)
	{
		ft_clean(str);
		return (NULL);
	}
	else
	{
		utls_ft_set(&str, ft_strdup(str + 1));
		return (str);
	}
}
