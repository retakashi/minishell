/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:38:45 by reira             #+#    #+#             */
/*   Updated: 2023/07/12 20:28:50 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

t_envp	*g_envp_list;

void	write_command_error(char *str)
{
	char	*error;

	error = ": command not found\n";
	write(2, str, ft_strlen(str));
	write(2, error, ft_strlen(error));
}

void	write_syntax_error(char *str)
{
	char	*error;

	error = "syntax error near unexpected token ";
	write(2, error, ft_strlen(error));
	write(2, "`", 1);
	write(2, str, ft_strlen(str));
	write(2, "'\n", 2);
}

void	write_env_error(void)
{
	char	*str;

	str = "env: No such file or directory\n";
	write(2, str, ft_strlen(str));
}

void	free_2d_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	put_error_free_2d_arr_exit(char *str, char **arr1, char **arr2, int flg)
{
	t_envp	*next;

	if (flg == COMMAND_ERROR)
		write_command_error(str);
	else if (flg == SYNTAX_ERROR)
		write_syntax_error(str);
	else if (flg == ENV_ERROR)
		write_env_error();
	else
		perror(str);
	if (arr1 != NULL)
		free_2d_arr(arr1);
	if (arr2 != NULL)
		free_2d_arr(arr2);
	free_g_list();
	exit(EXIT_FAILURE);
}
