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

// int	find_filename_to_pipe(t_word_list *word_list)
// {
// 	while (word_list != NULL && word_list->flag != pipe_char)
// 	{
// 		if (word_list->flag == input_file)
// 			return (true);
// 		if (word_list->flag == output_file)
// 			return (true);
// 		if (word_list->flag == append_file)
// 			return (true);
// 	}
// 	return (false);
// }

void	update_fd(char *filename, t_here_list *here_list, t_fd *fd_struct,
		int flg)
{
	if (flg == input_file)
	{
		if (here_list != NULL && here_list->here_fd == fd_struct->in_fd)
			if (close(here_list->here_fd) < 0)
				put_error_exit("close");
		fd_struct->in_fd = get_fd(filename, flg);
	}
	else if (flg == output_file)
	{
		if (fd_struct->out_fd != STDOUT_FILENO)
			if (close(fd_struct->out_fd) < 0)
				put_error_exit("close");
		fd_struct->out_fd = get_fd(filename, flg);
	}
	else
	{
		if (here_list != NULL && fd_struct->in_fd != STDIN_FILENO)
			if (close(fd_struct->in_fd) < 0)
				put_error_exit("close");
		fd_struct->in_fd = get_fd(here_list->here_file_name, flg);
	}
}

int	error_check_fd(t_fd *fd_struct)
{
	if (fd_struct->in_fd < 0)
		return (FAILURE);
	if (fd_struct->out_fd < 0)
		return (FAILURE);
	return (SUCCESS);
}

int	in_output_operation(t_word_list *word_list, t_here_list *here_list,
		t_fd *fd_struct, t_env_list **env_list)
{

	while (word_list != NULL && word_list->flag != pipe_char)
	{
		if (word_list->flag == input_file)
			update_fd(word_list->word, here_list, fd_struct, input_file);
		else if (word_list->flag == output_file)
			update_fd(word_list->word, here_list, fd_struct, output_file);
		else if (word_list->flag == append_file)
			update_fd(word_list->word, here_list, fd_struct, append_file);
		else if (word_list->flag == heredoc)
			update_fd(word_list->word, here_list, fd_struct, input_file);
		if (error_check_fd(fd_struct) == FAILURE)
			return (put_error_update_exit_status(word_list->word, env_list));
		word_list = word_list->next;
	}
	if (here_list != NULL && unlink(here_list->here_file_name) < 0)
		put_error_exit("unlink");
	return (SUCCESS);
}
