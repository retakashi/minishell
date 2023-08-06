/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:11:09 by reira             #+#    #+#             */
/*   Updated: 2023/08/07 01:10:04 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "libft/libft.h"

volatile sig_atomic_t	g_sig;

void	handle_sig_parent(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3",STDOUT_FILENO);
		ft_putstr_fd("\n",STDOUT_FILENO);
	}
}

int	set_signal_parent(void)
{
	struct sigaction	sigstruct;

	sigemptyset(&sigstruct.sa_mask);
	sigstruct.sa_flags = SA_RESTART;
	sigstruct.sa_handler = handle_sig_parent;
	if (sigaction(SIGINT, &sigstruct, NULL) == FAILURE)
		return (FAILURE);
	sigstruct.sa_handler = handle_sig_parent;
	sigstruct.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sigstruct, NULL) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
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
	sigstruct.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sigstruct, NULL) == FAILURE)
		return (FAILURE);
	if (sigaction(SIGQUIT, &sigstruct, NULL) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
