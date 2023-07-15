/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:17:41 by reira             #+#    #+#             */
/*   Updated: 2023/07/15 17:41:10 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	get_here_fd(t_word_list **word_head, t_fd *fd_struct)
{
	*word_head = (*word_head)->next;
	fd_struct->here_fd = open(".heredoc_file",
								O_WRONLY | O_CREAT | O_TRUNC,
								S_IREAD | S_IWRITE);
	if (fd_struct->here_fd < 0)
		perror_exit(".heredoc_file", 0);
}

void	create_heredoc(t_word_list **word_head, t_fd *fd_struct)
{
	int		flg;
	char	*line;

	get_here_fd(word_head, fd_struct);
	flg = 0;
	line = NULL;
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDOUT_FILENO, &flg);
		if (flg == 0 && line == NULL)
			perror_exit("failed to gnl", 0);
		if ((flg == 1 && line == NULL) || (ft_strcmp(line,
					(*word_head)->word) == 0))
			break ;
		ft_putstr_fd(line, fd_struct->here_fd);
		free(line);
	}
	if (line != NULL)
		free(line);
	if (close(fd_struct->here_fd) < 0)
		perror_exit("close", 0);
    *word_head=(*word_head)->next;
}
