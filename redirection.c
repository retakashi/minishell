/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:15:58 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/15 17:49:31 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	dup2_stdinput(t_word_list **word_list,t_fd *fd_struct)
{
	*word_list = (*word_list)->next;
	fd_struct->in_fd = open((*word_list)->word, O_RDONLY);
	if (fd_struct->in_fd < 0)
		perror_free_2d_arr_exit((*word_list)->word, NULL, NULL, NULL);
	if (dup2(fd_struct->in_fd, STDIN_FILENO) < 0)
		if (close(fd_struct->in_fd) < 0)
			perror_free_2d_arr_exit("close", NULL, NULL, NULL);
}

void	dup2_stdoutput(t_word_list **word_list,t_fd *fd_struct)
{
	*word_list = (*word_list)->next;
	fd_struct->out_fd = open((*word_list)->next,
			O_RDWR | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	if (fd_struct->out_fd < 0)
		perror_exit((*word_list)->word, 0);
	if (dup2(fd_struct->out_fd, STDOUT_FILENO) < 0)
		if (close(fd_struct->out_fd) < 0)
			perror_exit("close", 0);
}

void	main_redirection(t_word_list **word_list,t_fd *fd_struct)
{
	if ((*word_list)->flag == less)
		dup2_stdinput(word_list,fd_struct);
	else
		dup2_stdoutput(word_list,fd_struct);
	*word_list = (*word_list)->next;
}
