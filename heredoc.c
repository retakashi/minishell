/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:17:41 by reira             #+#    #+#             */
/*   Updated: 2023/07/21 21:15:08 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include "gnl/get_next_line.h"

void	get_here_fd(t_fd *fd_struct)
{
	fd_struct->here_fd = open(".heredoc_file",
								O_WRONLY | O_CREAT | O_TRUNC,
								S_IREAD | S_IWRITE);
	if (fd_struct->here_fd < 0)
		put_error(".heredoc_file", 0);
}

void	create_heredoc(t_word_list *word_list, t_fd *fd_struct)
{
	int		flg;
	char	*line;

	
	get_here_fd(fd_struct);
	flg = 0;
	line = NULL;
	advance_to_inequality_sign_arg(&word_list,less_less);
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDOUT_FILENO, &flg);
		if (flg == 0 && line == NULL)
			put_error_exit("failed to gnl");
		if ((flg == 1 && line == NULL) || (ft_strcmp(line,
					word_list->word) == 0))
			break ;
		ft_putstr_fd(line, fd_struct->here_fd);
		free(line);
	}
	if (line != NULL)
		free(line);
	if (close(fd_struct->here_fd) < 0)
		put_error("close", 0);
}
