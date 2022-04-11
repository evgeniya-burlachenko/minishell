/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 10:01:46 by zcris             #+#    #+#             */
/*   Updated: 2021/12/29 09:39:36 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_preparser(char *str)
{
	int	status;

	if (!(*str))
		return (0);
	status = utls_preparser_tests_dots(str);
	if (status != 0)
		return (status);
	status = utls_preparser_tests_single_quote(str);
	if (status != 0)
		return (status);
	status = utls_preparser_tests_start_pipe(str);
	if (status != 0)
		return (status);
	status = utls_preparser_tests_pipes(str);
	if (status != 0)
		return (status);
	status = utls_preparser_tests_redic(str);
	if (status != 0)
		return (status);
	return (status);
}

char	*utls_parser_str3join(char *start, char *inside, char *finish)
{
	char	*result;

	result = ft_strdup(start);
	if (result == NULL)
		return (NULL);
	if (inside != NULL)
		utls_ft_set(&result, ft_strjoin(result, inside));
	if (finish != NULL)
		utls_ft_set(&result, ft_strjoin(result, finish));
	return (result);
}

char	*utls_parser_get_dollar_key_from_str(char *str)
{
	int		i;

	i = 0;
	if (ft_strlen(str) == 1)
		return (ft_strdup("$"));
	if (utls_ft_is_space(str[1]))
		return (ft_strdup("$"));
	if (ft_isdigit(str[1]))
		return (ft_substr(str, 0, 2));
	while (str[++i])
	{
		if (!utls_ft_ifkey(str[i]))
			break ;
	}
	if (i == 1)
		return (ft_substr(str, 0, 2));
	return (ft_substr(str, 0, i));
}

char	*get_env_value(char *str, t_z_array *env)
{
	char	*result;

	if (ft_strlen(str) == 1)
		return (ft_strdup("$"));
	if (str[1] == '@' || ft_isdigit(str[1]))
		return (ft_strdup(""));
	if (str[1] == '?')
		return (utls_keys_value_get(PIPESTATUS, env));
	if (str[1] == '\'' || str[1] == '\"')
		return (ft_substr(str, 1, 1));
	if (!utls_ft_ifkey(str[1]))
		return (ft_strdup(str));
	result = utls_keys_value_get(str + 1, env);
	if (NULL == result)
		return (ft_strdup(""));
	return (result);
}

char	*set_env_inside_string(char *s, t_z_array *env, int *j, int *nl)
{
	int		i;
	char	*tmp;
	char	*tmp_start;
	char	*str;

	i = -1;
	str = ft_strdup(s);
	while (str[++i])
	{
		if (str[i] == '$')
		{
			tmp_start = ft_substr(str, 0, i);
			tmp = utls_parser_get_dollar_key_from_str(str + i);
			*j = ft_strlen(tmp) + i;
			utls_ft_set(&tmp, get_env_value(tmp, env));
			if (ft_strlen(tmp) == 0)
				*nl = 1;
			utls_ft_set(&str, ft_join_or_dup(tmp_start, tmp));
			utls_ft_4free(tmp, NULL, tmp_start, NULL);
			break ;
		}
	}
	return (str);
}
