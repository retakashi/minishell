/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:38:45 by reira             #+#    #+#             */
/*   Updated: 2023/07/22 13:14:37 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	command_error(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

void	exit_error(char *str)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

void	cd_error(char *str)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	perror(str);
}

int	put_error(char *str, int err_flg)
{
	if (err_flg == EXIT_ERROR)
	{
		exit_error(str);
		return (FAILURE);
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (err_flg == COMMAND_ERROR)
		command_error(str);
	else if (err_flg == CD_ERROR)
		cd_error(str);
	else if (err_flg == NO_ERRNO)
		ft_putstr_fd(str, STDERR_FILENO);
	else
		perror(str);
	return (FAILURE);
}

void	put_error_exit(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(str);
	exit(EXIT_FAILURE);
}
