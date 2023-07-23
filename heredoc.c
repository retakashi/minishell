/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:17:41 by reira             #+#    #+#             */
/*   Updated: 2023/07/23 21:12:26 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include "minishell.h"

char *get_file_name()
{
	char *file_name;
	int i;

	i=0;
	
}

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
			put_error_exit("failed to gnl",0);
		if ((flg == 1 && line == NULL) || (ft_strcmp(line, eof) == 0))
			break ;
		ft_putstr_fd(line, here_fd);
		free(line);
	}
	if (line != NULL)
		free(line);
}

int	main_heredoc(t_word_list *word_list, t_fd *fd_struct, t_env_list **env_list)
{
	char	*tmp_file_name;

	tmp_file_name = get_file_name();
	fd_struct->in_fd = get_fd(tmp_file_name, heredoc);
	if (fd_struct->in_fd < 0)
		return (put_error(tmp_file_name, 0, env_list));
	create_heredoc(word_list->word, fd_struct->in_fd);
	if (close(fd_struct->in_fd) < 0)
		return (put_error("close", 0, env_list));
	return (SUCCESS);
}
