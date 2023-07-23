/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:17:41 by reira             #+#    #+#             */
/*   Updated: 2023/07/23 00:21:20 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include "minishell.h"

void	create_heredoc(char *eof, int here_fd)
{
	int		flg;
	char	*line;

	flg = 0;
	line = NULL;
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDOUT_FILENO, &flg);
		if (flg == 0 && line == NULL)
			put_error_exit("failed to gnl");
		if ((flg == 1 && line == NULL) || (ft_strcmp(line, eof) == 0))
			break ;
		ft_putstr_fd(line, here_fd);
		free(line);
	}
	if (line != NULL)
		free(line);
}

int	main_heredoc(t_word_list *word_list, t_fd *fd_struct)
{
	while (word_list != NULL && word_list->flag != pipe_char)
	{
		if (word_list != NULL && word_list->flag == heredoc)
		{
			word_list = word_list->next;
			fd_struct->fd = get_fd(".heredoc", heredoc);
			if (fd_struct->fd < 0)
				return (put_error(".heredoc", 0));
			create_heredoc(word_list->word, fd_struct->fd);
		}
		word_list=word_list->next;
	}
	if (close(fd_struct->fd) < 0)
		return (put_error("close", 0));
	return(SUCCCESS);
}
