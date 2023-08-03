/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:17:17 by reira             #+#    #+#             */
/*   Updated: 2023/08/03 18:45:12 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"

char	*get_file_name(int i)
{
	char	*file_name;
	char	*file_num;

	file_num = ft_itoa(i);
	if (file_num == NULL)
		return (NULL);
	file_name = ft_strjoin("/tmp/.heredoc", file_num);
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
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			if (errno == ENOMEM)
				return (FAILURE);
			else
				break ;
		}
		if (ft_strcmp(line, eof) == 0)
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
		return (ft_perror((*node)->here_file_name));
	reset_signal();
	if (write_to_heredocfile(eof, (*node)->here_fd) == FAILURE)
		return (ft_perror("failed to write to heredocfile"));
	if (close((*node)->here_fd) < 0)
		return (ft_perror("close"));
	return (SUCCESS);
}
