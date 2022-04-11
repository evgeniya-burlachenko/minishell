/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _echo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:29:02 by zcris             #+#    #+#             */
/*   Updated: 2021/12/28 12:24:22 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '-')
			count++;
	}
	if (count != 1)
		return (0);
	if (ft_strncmp(str, "-", 1) == 0)
		return (1);
	return (0);
}

static void	handling_argv(t_z_array *argv, int *words, int *n_option)
{
	size_t	i;

	i = 1;
	if ((*argv).size == 0)
		return ;
	while (i < (*argv).size)
	{
		if (is_option((*argv).elem[i]))
		{
			(*n_option)++;
			z_array_remove(argv, i);
		}
		else
			break ;
	}
	i = 0;
	while (i < (*argv).size)
	{
		(*words)++;
		i++;
	}
}

int	builtins_echo(t_z_array *argv, t_z_array *envp)
{
	size_t	i;
	int		words;
	int		n_option;

	(void)envp;
	n_option = 0;
	words = 0;
	handling_argv(argv, &words, &n_option);
	i = 1;
	while (i < (*argv).size)
	{
		ft_putstr_fd((*argv).elem[i], STDOUT_FILENO);
		if (--words > 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (n_option == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
