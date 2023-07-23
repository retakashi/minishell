/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:38:45 by reira             #+#    #+#             */
/*   Updated: 2023/07/23 22:51:02 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	command_error(char *str, t_env_list **env_head)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	(*env_head)->exit_status = 127;
	return (FAILURE);
}

int	exit_error(char *str)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	return (FAILURE);
}

int	cd_error(char *str, t_env_list **env_head)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	perror(str);
	(*env_head)->exit_status = 1;
	return (FAILURE);
}

int export_error(char *str, t_env_list **env_head)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	(*env_head)->exit_status = 127;
	return (FAILURE);	
}

int	put_error(char *str, int err_flg, t_env_list **env_head)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (err_flg == COMMAND_ERROR)
		return (command_error(str, env_head));
	else if (err_flg == CD_ERROR)
		return (cd_error(str, env_head));
	else if (err_flg == EXPORT_ERROR)
		return (export_error(str, env_head));
	else if (err_flg == NO_ERRNO)
		ft_putstr_fd(str, STDERR_FILENO);
	else
	{
		perror(str);
		(*env_head)->exit_status = 1;
	}
	return (FAILURE);
}

void	put_error_exit(char *str, int flg)
{
	if (flg == EXIT_ERROR)
	{
		exit_error(str);
		exit(2);
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(str);
	exit(EXIT_FAILURE);
}
