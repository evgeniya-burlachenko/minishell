/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_preparser_tests.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 09:51:31 by skelly            #+#    #+#             */
/*   Updated: 2021/12/25 16:57:32 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	utls_preparser_tests_single_quote(char *str)
{
	int	i;
	int	is_quote;

	is_quote = 0;
	i = -1;
	while (str[++i])
	{
		if ((str[i] == '\'' && is_quote == 1) || (str[i] == '\"'\
		&& is_quote == 2))
			is_quote = 0;
		else if (str[i] == '\'' && !is_quote)
			is_quote = 1;
		else if (str[i] == '\"' && !is_quote)
			is_quote = 2;
	}
	if (is_quote != 0)
	{
		utls_print_error(ERROR_QUOTES);
		return (258);
	}
	return (is_quote);
}

int	utls_preparser_tests_pipes(char *str)
{
	int	i;
	int	is_quote;
	int	is_pipe;

	is_pipe = 0;
	is_quote = -1;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"')
			is_quote = -is_quote;
		if (str[i] == '|' && is_quote < 0)
		{
			if (is_pipe > 0)
			{
				utls_print_errno(ERRORS_NOT_TOKEN, "|", NULL);
				return (258);
			}
			else
				is_pipe = 1;
		}
		else if (!utls_ft_is_space(str[i]))
			is_pipe = 0;
	}
	return (0);
}

int	utls_preparser_tests_start_pipe(char *str)
{
	if (str[0] == '|')
	{
		utls_print_errno(ERRORS_NOT_TOKEN, "|", NULL);
		return (258);
	}
	return (0);
}

int	utls_preparser_tests_redic(char *str)
{
	size_t	size;

	size = ft_strlen(str);
	if (str[size - 1] == '<' || str[size - 1] == '>')
	{
		utls_print_errno(ERRORS_NOT_TOKEN, "newline", NULL);
		return (258);
	}
	if (str[size - 1] == '|' || str[size - 1] == '|')
	{
		utls_print_errno(ERRORS_NOT_TOKEN, "|", NULL);
		return (258);
	}
	return (0);
}

int	utls_preparser_tests_dots(char *str)
{
	size_t	size;

	size = ft_strlen(str);
	if (utls_ft_strcmp(str, "..") == 0 || utls_ft_strcmp(str, ".") == 0)
	{
		utls_print_errno(NULL, str, ERRORS_127);
		return (127);
	}
	if (size > 1)
	{
		if (str[0] == '.')
		{
			if (str[1] != '/' && str[1] != '.')
			{
				utls_print_errno(NULL, str, ERRORS_127);
				return (127);
			}
		}
	}
	return (0);
}
