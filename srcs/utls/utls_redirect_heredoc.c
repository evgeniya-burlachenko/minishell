/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_redirect_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skelly <skelly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 10:28:56 by zcris             #+#    #+#             */
/*   Updated: 2022/04/11 23:19:10 by skelly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	init_reinit(int flag)
{
	static int	(*f)(FILE *);

	if (flag == 1)
	{
		rl_catch_signals = 1;
		signals_heredoc();
		f = rl_getc_function;
		rl_getc_function = getc;
		return ;
	}
	if (flag == 0)
	{
		signals_init();
		rl_getc_function = f;
		rl_catch_signals = 0;
		return ;
	}
}

void	ft_heredoc(int *i, char *stop_word)
{
	char	*read_buff;
	int		fd[2];

	if (*i > 0)
		close(*i);
	pipe(fd);
	init_reinit(1);
	while (1)
	{
		read_buff = readline(PROMPTHERDOC);
		if (NULL == read_buff)
			break ;
		if (utls_ft_strcmp(read_buff, stop_word) == 0)
			break ;
		write(fd[1], read_buff, ft_strlen(read_buff));
		write(fd[1], "\n", 1);
		free(read_buff);
	}
	init_reinit(0);
	close(fd[1]);
	free(read_buff);
	*i = fd[0];
}
