/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:38:45 by reira             #+#    #+#             */
/*   Updated: 2023/07/15 17:31:06 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	write_command_error(char *str)
{
	char	*error;

	error = ": command not found\n";
	write(2, str, ft_strlen(str));
	write(2, error, ft_strlen(error));
}

void	write_env_error(void)
{
	char	*str;

	str = "env: No such file or directory\n";
	write(2, str, ft_strlen(str));
}

void	put_error_free_2d_arr_exit(char *str,int error_flg)
{

	if (error_flg == COMMAND_ERROR)
		write_command_error(str);
	else if (error_flg == ENV_ERROR)
		write_env_error();
	else
		perror(str);
	exit(EXIT_FAILURE);
}
