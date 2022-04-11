/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 09:32:55 by zcris             #+#    #+#             */
/*   Updated: 2021/12/30 11:10:38 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtins_exit_is_number(char *str)
{
	size_t	i;

	i = 1;
	if (!(ft_isdigit(str[0]) || str[0] == '-' || str[0] == '+'))
		return (1);
	while (str[i])
	{
		if (!(ft_isdigit(str[i])))
			return (1);
		i++;
	}
	if (str[0] == '-' && ft_strncmp(str, "-9223372036854775808", 21) > 0)
		return (1);
	if (ft_strncmp(str, "9223372036854775807", 21) > 0)
		return (1);
	return (0);
}

int	builtins_exit(t_z_array *argv, t_z_array *envp)
{
	(void)envp;
	utls_print_error("exit\n");
	if ((*argv).size == 1)
		exit (0);
	else if (builtins_exit_is_number((*argv).elem[1]))
	{
		utls_print_errno("exit", (*argv).elem[1], ERRORS_REQ_NUMBER);
		exit (255);
	}
	else if ((*argv).size > 2)
	{
		utls_print_errno("exit", NULL, ERRORS_TOO_MANY);
		return (1);
	}
	else
		exit (((unsigned int)ft_atoi((*argv).elem[1])) % 256);
	return (0);
}
