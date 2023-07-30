/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 02:21:09 by reira             #+#    #+#             */
/*   Updated: 2023/07/30 23:28:07 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

void	in_out_file_dup2(t_fd fd_struct, t_word_list **word_list,
		t_env_list **env_list)
{
	if (fd_struct.in_fd != STDIN_FILENO && dup2(fd_struct.in_fd,
			STDIN_FILENO) < 0)
	{
		ft_perror("dup2");
		free_list_exit(word_list, env_list, NULL,EXIT_FAILURE);
	}
	if (fd_struct.out_fd != STDOUT_FILENO && dup2(fd_struct.out_fd,
			STDOUT_FILENO) < 0)
	{
		ft_perror("dup2");
		free_list_exit(word_list, env_list, NULL,EXIT_FAILURE);
	}
}

void	close_middle_pipe(t_p_data p_data, t_word_list **word_list,
		t_env_list **env_list)
{
	if (close(p_data.pipe_2darr[p_data.i - 1][WRITE]) < 0)
	{
		ft_perror("close");
		free_list_pipe2darr_exit(p_data, word_list, env_list);
	}
	if (close(p_data.pipe_2darr[p_data.i][READ]) < 0)
	{
		ft_perror("close");
		free_list_pipe2darr_exit(p_data, word_list, env_list);
	}
}

void	close_pipe(t_p_data p_data, t_word_list **word_list,
		t_env_list **env_list)
{
	if (p_data.i == 0 && close(p_data.pipe_2darr[0][READ]) < 0)
	{
		ft_perror("close");
		free_list_pipe2darr_exit(p_data, word_list, env_list);
	}
	else if (p_data.i == p_data.cnt+1 && close(p_data.pipe_2darr[p_data.cnt-1][WRITE]) < 0)
	{
		ft_perror("close");
		free_list_pipe2darr_exit(p_data, word_list, env_list);
	}
	else
		close_middle_pipe(p_data, word_list, env_list);
}

void	dup2_middle_pipe(t_p_data p_data, t_word_list **word_list,
		t_env_list **env_list)
{
	if (dup2(p_data.pipe_2darr[p_data.i - 1][READ], STDIN_FILENO) < 0)
	{
		ft_perror("dup2");
		free_list_pipe2darr_exit(p_data, word_list, env_list);
	}
	if (dup2(p_data.pipe_2darr[p_data.i][WRITE], STDOUT_FILENO) < 0)
	{
		ft_perror("dup2");
		free_list_pipe2darr_exit(p_data, word_list, env_list);
	}
}

void	dup2_close_pipe(t_p_data p_data, t_word_list **word_list,
		t_env_list **env_list)
{
	if (p_data.i == 0 && dup2(p_data.pipe_2darr[0][WRITE], STDOUT_FILENO) < 0)
	{
		ft_perror("dup2");
		free_list_pipe2darr_exit(p_data, word_list, env_list,
				);
	}
	else if (p_data.i == p_data.cnt && dup2(p_data.pipe_2darr[p_data.cnt-1][READ],
				STDOUT_FILENO) < 0)
	{
		ft_perror("dup2");
		free_list_pipe2darr_exit(p_data, word_list, env_list,
				);
	}
	else
		dup2_middle_pipe(p_data, word_list, env_list);
	close_pipe(p_data, word_list, env_list);
}
