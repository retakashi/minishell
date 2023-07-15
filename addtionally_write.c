/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addtionally_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:31:53 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/15 16:39:50 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	read_heredoc(t_fd *fd_struct)
{
	fd_struct->here_fd = open(".heredoc_file", O_RDONLY);
	if (fd_struct->here_fd < 0)
		perror_exit(".heredoc_file", 0);
	if (unlink(".heredoc_file") < 0)
		perror_exit("unlink", 0);
	if (dup2(fd_struct->here_fd, STDIN_FILENO) < 0)
		perror_exit("dup2", 0);
	if (close(fd_struct->here_fd) < 0)
		perror_exit("close", 0);
}

void	additionally_write(t_word_list **word_head, t_fd *fd_struct)
{
	*word_head = (*word_head)->next;
	fd_struct->out_fd = open((*word_head)->word,
								O_RDWR | O_CREAT | O_APPEND,
								S_IREAD | S_IWRITE);
	if (dup2(fd_struct->out_fd, STDOUT_FILENO) < 0)
		put_error_free_2d_arr_exit("dup2", NULL, NULL, NULL);
	if (close(fd_struct->out_fd) < 0)
		put_error_free_2d_arr_exit("close", NULL, NULL, NULL);
}
