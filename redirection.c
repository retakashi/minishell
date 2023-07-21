/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:15:58 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/22 00:10:46 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	dup2_stdinput(t_word_list *word_list, t_fd *fd_struct)
{
	fd_struct->in_fd = open(word_list->word, O_RDONLY);
	if (fd_struct->in_fd < 0)
		put_error(word_list->word, 0);
	if (dup2(fd_struct->in_fd, STDIN_FILENO) < 0)
		if (close(fd_struct->in_fd) < 0)
			put_error("close", 0);
}

void	dup2_stdoutput(t_word_list *word_list, t_fd *fd_struct)
{
	fd_struct->out_fd = open(word_list->word,
								O_RDWR | O_CREAT | O_TRUNC,
								S_IREAD | S_IWRITE);
	if (fd_struct->out_fd < 0)
		put_error(word_list->word, 0);
	if (dup2(fd_struct->out_fd, STDOUT_FILENO) < 0)
	dup2(fd_struct->out_fd,10);
		if (close(fd_struct->out_fd) < 0)
			put_error("close", 0);
}

void	main_redirection(t_word_list *word_list, t_fd *fd_struct,int red_flg)
{
	if (red_flg == less)
	{
		advance_to_inequality_sign_arg(&word_list, less);
		dup2_stdinput(word_list, fd_struct);
	}
	else
	{
		advance_to_inequality_sign_arg(&word_list, great);
		dup2_stdoutput(word_list, fd_struct);
	}
}
