/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:11:09 by reira             #+#    #+#             */
/*   Updated: 2023/08/03 18:51:47 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "libft/libft.h"

int		g_sig;

void	reset_signal(void)
{
	if (g_sig == SIGINT)
		signal(g_sig, SIG_DFL);
	else if (g_sig == SIGQUIT)
		signal(g_sig, SIG_DFL);
}
void signal_heredoc(int sig)
{
    if(sig==SIGINT)
    {
        g_sig=SIGINT;
        
    }
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		g_sig = SIGQUIT;
        
}

void	set_signal_handler(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
