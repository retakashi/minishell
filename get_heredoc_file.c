/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:17:17 by reira             #+#    #+#             */
/*   Updated: 2023/07/28 17:45:04 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"

char	*get_file_name(int i)
{
	char	*file_name;
	char	*file_num;

	file_num = ft_itoa(i);
	file_name = ft_strjoin(".heredoc", file_num);
	if (file_name == NULL)
	{
		free(file_num);
		return (NULL);
	}
	free(file_num);
	if (access(file_name, F_OK) < 0)
		return (file_name);
	free(file_name);
	return (get_file_name(i + 1));
}

static int	write_to_heredocfile(char *eof, int fd)
{
	int		flg;
	char	*line;
	size_t	eof_len;

	flg = 0;
	line = NULL;
	eof_len = ft_strlen(eof);
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDOUT_FILENO, &flg);
		if (flg == 0 && line == NULL)
			return (FAILURE);
		if ((flg == 1 && line == NULL) || (ft_strncmp(line, eof, eof_len) == 0
				&& line[eof_len] == '\n'))
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	if (line != NULL)
		free(line);
	return (SUCCESS);
}

int	get_heredoc_file(t_here_list **node, char *eof)
{
	(*node)->here_fd = get_fd((*node)->here_file_name, heredoc);
	if ((*node)->here_fd < 0)
		return (FAILURE);
	if (write_to_heredocfile(eof, (*node)->here_fd) == FAILURE)
		return (FAILURE);
	if (close((*node)->here_fd) < 0)
		return (FAILURE);
	return (SUCCESS);
}
