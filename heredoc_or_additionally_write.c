/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_or_additionally_write.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:31:53 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/13 17:44:28 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	get_here_fd(t_word_list **word_head)
{
	if ((*word_head)->next == NULL)
		put_error_free_2d_arr_exit("newline", NULL, NULL, SYNTAX_ERROR);
	*word_head = (*word_head)->next;
	g_envp_list->fd_struct->here_fd = open(".heredoc_file",
											O_WRONLY | O_CREAT | O_TRUNC,
											S_IREAD | S_IWRITE);
	if (g_envp_list->fd_struct->here_fd < 0)
		put_error_free_2d_arr_exit(".heredoc_file", NULL, NULL, SYNTAX_ERROR);
}

void	create_heredoc(t_word_list **word_head)
{
	int		flg;
	char	*line;

	get_here_fd(word_head);
	flg = 0;
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDOUT_FILENO, &flg);
		if (flg == 0 && line == NULL)
			put_error_free_2d_arr_exit("failed to gnl", NULL, NULL, NULL);
		if ((flg == 1 && line == NULL) || (ft_strcmp(line,
					(*word_head)->word) == 0))
			break ;
		ft_putstr_fd(line, g_envp_list->fd_struct->here_fd);
		free(line);
	}
	if (line != NULL)
		free(line);
	if (close(g_envp_list->fd_struct->here_fd) < 0)
		free_perror_exit("close", NULL, NULL, NULL);
}

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

void	main_heredoc_or_additionally_write(t_word_list **word_head)
{
	if ((*word_head)->flag == less_less)
		create_heredoc(&word_head);
	else
		additionally_write(&word_head);
}
