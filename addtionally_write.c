/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addtionally_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:31:53 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/21 21:13:11 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	read_heredoc(t_fd *fd_struct)
{
	fd_struct->here_fd = open(".heredoc_file", O_RDONLY);
	if (fd_struct->here_fd < 0)
		put_error(".heredoc_file", 0);
	if (unlink(".heredoc_file") < 0)
		put_error("unlink", 0);
	if (dup2(fd_struct->here_fd, STDIN_FILENO) < 0)
		put_error("dup2", 0);
	if (close(fd_struct->here_fd) < 0)
		put_error("close", 0);
}

void	additionally_write(t_word_list *word_list, t_fd *fd_struct)
{
	advance_to_inequality_sign_arg(&word_list,great_great);
	fd_struct->out_fd = open(word_list->word,
								O_RDWR | O_CREAT | O_APPEND,
								S_IREAD | S_IWRITE);
	if (dup2(fd_struct->out_fd, STDOUT_FILENO) < 0)
		put_error("dup2", 0);
	if (close(fd_struct->out_fd) < 0)
		put_error("close", 0);
}
