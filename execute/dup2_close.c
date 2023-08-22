/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 02:21:09 by reira             #+#    #+#             */
/*   Updated: 2023/08/20 19:36:58 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute_cmd.h"

int	dup2_fd_struct(t_fd fd_struct)
{
	if (fd_struct.in_fd != STDIN_FILENO)
	{
		if (dup2(fd_struct.in_fd,
				STDIN_FILENO) < 0)
			return (ft_perror("dup2"));
		if (close(fd_struct.in_fd) < 0)
			return (ft_perror("close"));
	}
	if (fd_struct.out_fd != STDOUT_FILENO)
	{
		if (dup2(fd_struct.out_fd,
				STDOUT_FILENO) < 0)
			return (ft_perror("dup2"));
		if (close(fd_struct.out_fd) < 0)
			return (ft_perror("close"));
	}
	return (SUCCESS);
}

void	dup2_pipe(t_f_data f_data, t_word_list **word_list,
		t_env_list **env_list)
{
	if (f_data.i == 0)
	{
		if (dup2(f_data.pipe_2darr[f_data.i][WRITE], STDOUT_FILENO) < 0)
			put_error_exit_cmdsver("dup2", f_data, word_list, env_list);
	}
	else if (f_data.i == f_data.cnt)
	{
		if (dup2(f_data.pipe_2darr[f_data.i - 1][READ], STDIN_FILENO) < 0)
			put_error_exit_cmdsver("dup2", f_data, word_list, env_list);
	}
	else
	{
		if (dup2(f_data.pipe_2darr[f_data.i - 1][READ], STDIN_FILENO) < 0)
			put_error_exit_cmdsver("dup2", f_data, word_list, env_list);
		if (dup2(f_data.pipe_2darr[f_data.i][WRITE], STDOUT_FILENO) < 0)
			put_error_exit_cmdsver("dup2", f_data, word_list, env_list);
	}
}

static void	close_first_pipe(t_f_data f_data, t_word_list **word_list,
		t_env_list **env_list)
{
	if (close(f_data.pipe_2darr[f_data.i][WRITE]) < 0)
		put_error_exit_cmdsver("close", f_data, word_list, env_list);
	if (close(f_data.pipe_2darr[f_data.i][READ]) < 0)
		put_error_exit_cmdsver("close", f_data, word_list, env_list);
}

static void	close_last_pipe(t_f_data f_data, t_word_list **word_list,
		t_env_list **env_list)
{
	if (close(f_data.pipe_2darr[f_data.i - 1][WRITE]) < 0)
		put_error_exit_cmdsver("close", f_data, word_list, env_list);
	if (close(f_data.pipe_2darr[f_data.i - 1][READ]) < 0)
		put_error_exit_cmdsver("close", f_data, word_list, env_list);
}

void	close_pipe(t_f_data f_data, t_word_list **word_list,
		t_env_list **env_list)
{
	if (f_data.i == 0)
		close_first_pipe(f_data, word_list, env_list);
	else if (f_data.i == f_data.cnt)
		close_last_pipe(f_data, word_list, env_list);
	else
	{
		close_first_pipe(f_data, word_list, env_list);
		close_last_pipe(f_data, word_list, env_list);
	}
}
