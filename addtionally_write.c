/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addtionally_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:31:53 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/14 16:19:39 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"




void	read_heredoc(void)
{
	g_envp_list->fd_struct->here_fd = open(".heredoc_file", O_RDONLY);
	if (g_envp_list->fd_struct->here_fd < 0)
		put_error_free_2d_arr_exit(".heredoc_file", NULL, NULL, NULL);
	if (unlink(".heredoc_file") < 0)
		put_error_free_2d_arr_exit("unlink", NULL, NULL, NULL);
	if (dup2(g_envp_list->fd_struct->here_fd, STDIN_FILENO) < 0)
		put_error_free_2d_arr_exit("dup2", NULL, NULL, NULL);
	if (close(g_envp_list->fd_struct->here_fd) < 0)
		put_error_free_2d_arr_exit("close", NULL, NULL, NULL);
}

void	additionally_write(t_word_list **word_head)
{
	if ((*word_head)->next == NULL)
		put_error_free_2d_arr_exit("newline", NULL, NULL, SYNTAX_ERROR);
	*word_head = (*word_head)->next;
	g_envp_list->fd_struct->out_fd = open((*word_head)->word,
			O_RDWR | O_CREAT | O_APPEND, S_IREAD | S_IWRITE);
	if (dup2(g_envp_list->fd_struct->out_fd, STDOUT_FILENO) < 0)
		put_error_free_2d_arr_exit("dup2", NULL, NULL, NULL);
	if (close(g_envp_list->fd_struct->out_fd) < 0)
		put_error_free_2d_arr_exit("close", NULL, NULL, NULL);
}

void	main_additionally_write(t_word_list **word_head)
{
	if ((*word_head)->flag == less_less)
		create_heredoc(&word_head);
	else
		additionally_write(&word_head);
}
