/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcris <zcris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 07:08:58 by zcris             #+#    #+#             */
/*   Updated: 2021/12/29 09:51:44 by zcris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signals_cut_ctrl(void)
{
	char	*tmp;
	char	*cleaner;

	tmp = ft_strdup(rl_line_buffer);
	cleaner = ft_strjoin(rl_line_buffer, "  ");
	utls_ft_memset(&cleaner, ' ');
	rl_on_new_line();
	rl_replace_line(cleaner, 0);
	rl_redisplay();
	rl_replace_line(tmp, 0);
	free(tmp);
	free(cleaner);
	rl_redisplay();
}

static void	signals_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("\0", 0);
		rl_redisplay();
	}
}

static void	signals_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		signals_cut_ctrl();
	}
}

void	signals_init(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signals_handler);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	signals_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signals_handler_heredoc);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
