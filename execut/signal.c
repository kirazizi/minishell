/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:37:27 by sbzizal           #+#    #+#             */
/*   Updated: 2023/08/13 22:00:25 by sbzizal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	herdoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status.exit_status = 1;
		g_status.heredoc = 1;
		close(0);
	}
}

void	sig_catch(int signo)
{
	(void)signo;
	return ;
}

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_status.exit_status = 1;
	}
}

void	ft_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_catch_signal(void)
{
	signal(SIGINT, sig_catch);
	signal(SIGQUIT, sig_catch);
}
