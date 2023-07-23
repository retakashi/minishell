/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:17:41 by reira             #+#    #+#             */
/*   Updated: 2023/07/24 02:12:25 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include "minishell.h"

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

int	create_heredoc(char *eof, int fd)
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
			return (FAILURE);
		if ((flg == 1 && line == NULL) || (ft_strcmp(line, eof) == 0))
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	if (line != NULL)
		free(line);
	return (SUCCESS);
}

int	new_here_node(t_here *new, char *eof)
{
	new = malloc(sizeof(t_here));
	if (new == NULL)
		return (FAILURE);
	new->here_file_name = get_file_name(0);
	if (new->here_file_name == NULL)
		return (FAILURE);
	new->here_fd = get_fd(new->here_file_name, heredoc);
	if (new->here_fd < 0)
		return (FAILURE);
	return (SUCCESS);
}

int	change_here_file(t_here *node, char *eof)
{
	if (unlink(node->here_file_name) < 0)
		return (FAILURE);
	free(node->here_file_name);
	if (close(node->here_fd) < 0)
		return (FAILURE);
	node->here_file_name = get_file_name(0);
	if (node->here_file_name == NULL)
		return (FAILURE);
	node->here_fd = get_fd(node->here_file_name, heredoc);
	if (node->here_fd < 0)
		return (FAILURE);
	return (SUCCESS);
}

int	main_heredoc(t_word_list *word_list, t_fd *fd_struct, t_env_list **env_list)
{
	int		pipe_flg;
	t_here	*here_node;
	t_here	*here_new;

	pipe_flg = false;
	if (new_here_node(&here_node, word_list->word) == FAILURE)
		return (put_error("failed to new_here_node", 0, env_list));
	fd_struct->here_list_head = here_node;
	word_list = word_list->next;
	while (word_list != NULL)
	{
		if (pipe_flg == false && word_list->flag == pipe_char)
			pipe_flg = true;
		if (pipe_flg == true && word_list->flag == heredoc_file)
		{
			if (new_here_node(&here_new, word_list->word) == FAILURE)
				return (put_error("failed to new_here_node", 0, env_list));
			here_node->next = here_new;
			here_node = here_new;
		}
		if (pipe_flg == true && word_list->flag == pipe_char)
			pipe_flg = false;
		if ((pipe_flg == false && word_list->flag == heredoc_file)
			&& change_here_node(&here_node, word_list->word) == FAILURE)
			return (put_error("failed to change_here_node", 0, env_list));
		word_list = word_list->next;
	}
	return (SUCCESS);
}
