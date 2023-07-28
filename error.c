/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:38:45 by reira             #+#    #+#             */
/*   Updated: 2023/07/28 14:55:23 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "execve_cmd.h"

int	put_cd_error_update_exit_status(char *str, t_env_list **env_head)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	if(*env_head!=NULL)
	(*env_head)->exit_status = 1;
	return (FAILURE);
}

void	command_error(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);	
}

int	cd_error(char *str, t_env_list **env_head)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	perror(str);
	if(*env_head!=NULL)
	(*env_head)->exit_status = 1;
	return (FAILURE);
}

int	env_error(char *str, t_env_list **env_head)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	if(*env_head!=NULL)
	(*env_head)->exit_status = 127;
	return (FAILURE);
}

int	put_error_update_exit_status(char *str, t_env_list **env_head)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(str);
	if(*env_head!=NULL)
	(*env_head)->exit_status = 1;
	return (FAILURE);
}

void	exit_error(char *str)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

void	put_error_exit(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(str);
	exit(EXIT_FAILURE);
}
