/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:38:45 by reira             #+#    #+#             */
/*   Updated: 2023/08/02 16:57:03 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "libft/libft.h"

int	put_error(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	return (FAILURE);
}

int	ft_perror(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(str);
	return (FAILURE);
}

void	command_error(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

char	**perror_change_err_flg(char *err_msg, int *err_flg)
{
	ft_perror(err_msg);
	*err_flg = true;
	return (NULL);
}

int	update_exit_status(t_env_list **env_list)
{
	free((*env_list)->env_value);
	(*env_list)->env_value = ft_strdup("1");
	if ((*env_list)->env_value == NULL)
		return (ft_perror("ft_strdup"));
	return (FAILURE);
}
