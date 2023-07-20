/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:38:45 by reira             #+#    #+#             */
/*   Updated: 2023/07/20 23:04:51 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

extern t_shell	*g_shell_struct;

void	write_command_error(char *str)
{
	char	*error;

	error = ": command not found\n";
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
}

void	write_env_error(void)
{
	char	*str;

	str = "env: No such file or directory\n";
	ft_putstr_fd(str, STDERR_FILENO);
}

void	write_exit_error(char *str)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDOUT_FILENO);
	exit(2);
}

void	perror_exit(char *str, int error_flg)
{
	if (error_flg == COMMAND_ERROR)
		write_command_error(str);
	else if (error_flg == ENV_ERROR)
		write_env_error();
	else if (error_flg == EXIT_ERROR)
		write_exit_error(str);
	else
		perror(str);
	exit(EXIT_FAILURE);
}
