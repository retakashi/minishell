/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_outputput_operarion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:58:02 by reira             #+#    #+#             */
/*   Updated: 2023/07/22 18:17:41 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

static int	update_fd(char *filename, t_here_list *here_list, t_fd *fd_struct,
		int flg)
{
	if (flg == input_file)
	{
		if (here_list != NULL && here_list->here_fd == fd_struct->in_fd)
			if (close(here_list->here_fd) < 0)
				return (FAILURE);
		fd_struct->in_fd = get_fd(filename, flg);
	}
	else if (flg == output_file)
	{
		if (fd_struct->out_fd != STDOUT_FILENO)
			if (close(fd_struct->out_fd) < 0)
				return (FAILURE);
		fd_struct->out_fd = get_fd(filename, flg);
	}
	else
	{
		if (here_list != NULL && fd_struct->in_fd != STDIN_FILENO)
			if (close(fd_struct->in_fd) < 0)
				return (FAILURE);
		fd_struct->in_fd = get_fd(here_list->here_file_name, flg);
	}
	return(SUCCESS);
}

static int	error_check_fd(t_fd *fd_struct)
{
	if (fd_struct->in_fd < 0)
		return (FAILURE);
	if (fd_struct->out_fd < 0)
		return (FAILURE);
	return (SUCCESS);
}

int	change_exit_error_flg(int *exit_error_flg)
{
	*exit_error_flg = true;
	return (FAILURE);
}

static void	init_fd_struct(t_fd *fd_struct)
{
	fd_struct->in_fd = STDIN_FILENO;
	fd_struct->out_fd = STDOUT_FILENO;
}

int	in_output_operation(t_word_list *word_list, t_here_list *here_list,
		t_fd *fd_struct, int *exit_error_flg)
{
	init_fd_struct(fd_struct);
	while (word_list != NULL && word_list->flag != pipe_char)
	{
		if (word_list->flag == input_file && update_fd(word_list->word,
				here_list, fd_struct, input_file) == FAILURE)
			return (change_exit_error_flg(exit_error_flg));
		else if (word_list->flag == output_file && update_fd(word_list->word,
				here_list, fd_struct, output_file) == FAILURE)
			return (change_exit_error_flg(exit_error_flg));
		else if (word_list->flag == append_file && update_fd(word_list->word,
				here_list, fd_struct, append_file) == FAILURE)
			return (change_exit_error_flg(exit_error_flg));
		else if (word_list->flag == heredoc && update_fd(word_list->word,
				here_list, fd_struct, input_file) == FAILURE)
			return (change_exit_error_flg(exit_error_flg));
		if (error_check_fd(fd_struct) == FAILURE)
			return (FAILURE);
		word_list = word_list->next;
	}
	if (here_list != NULL && unlink(here_list->here_file_name) < 0)
		return (change_exit_error_flg(exit_error_flg));
	return (change_exit_error_flg(exit_error_flg));
// 	return (SUCCESS);
}
