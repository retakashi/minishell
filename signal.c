/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:11:09 by reira             #+#    #+#             */
/*   Updated: 2023/08/03 21:42:59 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "libft/libft.h"

volatile sig_atomic_t g_sig;

void	reset_signal(void)
{
	printf("hello\n");
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handler_here(int sig)
{
	if (sig == SIGINT)
		g_sig = 1;
}

void	signal_heredoc(void)
{
	signal(SIGINT, signal_handler_here);
	signal(SIGQUIT, signal_handler);
}

void	set_signal_handler(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
