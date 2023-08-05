/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:11:09 by reira             #+#    #+#             */
/*   Updated: 2023/08/05 18:40:57 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "libft/libft.h"

volatile sig_atomic_t	g_sig;

void	handle_signal_execve(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3", STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

int	set_signal_execve(void)
{
	struct sigaction	sigstruct;

	sigemptyset(&sigstruct.sa_mask);
	sigstruct.sa_handler = handle_signal_execve;
	sigstruct.sa_flags = 0;
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		return (FAILURE);
	if (sigaction(SIGQUIT, &sigstruct, NULL) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_sig=SIGINT;
		rl_on_new_line();
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	set_sigint(void)
{
	struct sigaction	sigstruct;

	sigemptyset(&sigstruct.sa_mask);
	sigstruct.sa_handler = handle_sigint;
	sigstruct.sa_flags = 0;
	if (sigaction(SIGINT, &sigstruct, NULL) == FAILURE)
		return (FAILURE);
	if (sigaction(SIGQUIT, &sigstruct, NULL) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
