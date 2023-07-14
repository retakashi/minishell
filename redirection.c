/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:15:58 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/14 17:01:51 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	dup2_stdinput(t_word_list **word_head)
{
	if ((*word_head)->next == NULL)
		put_error_free_2d_arr_exit("newline", NULL, NULL, SYNTAX_ERROR);
	*word_head = (*word_head)->next;
	g_envp_list->fd_struct->in_fd = open((*word_head)->word, O_RDONLY);
	if (g_envp_list->fd_struct->in_fd < 0)
		perror_free_2d_arr_exit((*word_head)->word, NULL, NULL, NULL);
	if (dup2(g_envp_list->fd_struct->in_fd, STDIN_FILENO) < 0)
		if (close(g_envp_list->fd_struct->in_fd) < 0)
			perror_free_2d_arr_exit("close", NULL, NULL, NULL);
}

void	dup2_stdoutput(t_word_list **word_head)
{
	if ((*word_head)->next == NULL)
		put_error_free_2d_arr_exit("newline", NULL, NULL, SYNTAX_ERROR);
	*word_head = (*word_head)->next;
	g_envp_list->fd_struct->out_fd = open((*word_head)->next,
			O_RDWR | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	if (g_envp_list->fd_struct->out_fd < 0)
		perror_free_2d_arr_exit((*word_head)->word, NULL, NULL, NULL);
	if (dup2(g_envp_list->fd_struct->out_fd, STDOUT_FILENO) < 0)
		if (close(g_envp_list->fd_struct->out_fd) < 0)
			perror_free_2d_arr_exit("close", NULL, NULL, NULL);
}

void	main_redirection(t_word_list **word_head,t_fd *fd_struct)
{
	if ((*word_head)->flag == less)
		dup2_stdinput(&word_head);
	else
		dup2_stdoutput(&word_head);
	*word_head = (*word_head)->next;
}
