/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:17:41 by reira             #+#    #+#             */
/*   Updated: 2023/07/24 21:49:28 by reira            ###   ########.fr       */
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

int	new_here_node(t_fd *new, char *eof,t_env_list **env_list)
{
	new = malloc(sizeof(t_fd));
	if (new == NULL)
		put_error_exit("failed to new_here_node");
	new->here_file_name = get_file_name(0);
	if (new->here_file_name == NULL)
		put_error_exit("failed to get_file_name");
	new->in_fd = get_fd(new->here_file_name, heredoc);
	if (new->in_fd < 0)
		return (put_error_update_exit_status(new->here_file_name, env_list));
	new->out_fd = STDOUT_FILENO;
	if (create_heredoc(eof, new->in_fd) == FAILURE)
		put_error_exit("failed to gnl");
	new->pipe_cnt = 0;
	return (SUCCESS);
}

int	change_here_file(t_fd *node, char *eof, t_env_list **env_list)
{
	if (unlink(node->here_file_name) < 0)
		return (put_error_update_exit_status("unlink", env_list));
	free(node->here_file_name);
	if (close(node->in_fd) < 0)
		return (put_error_update_exit_status("close", env_list));
	node->here_file_name = get_file_name(0);
	if (node->here_file_name == NULL)
		put_error_exit("failed to get_file_name");
	node->in_fd = get_fd(node->here_file_name, heredoc);
	if (node->in_fd < 0)
		return (put_error_update_exit_status(node->here_file_name, env_list));
	if (create_heredoc(eof, node->in_fd) == FAILURE)
		put_error_exit("failed to gnl");
	return (SUCCESS);
}

int	main_heredoc(t_word_list *word_list, t_fd **fd_list, t_env_list **env_list)
{
	t_fd	*here_node;
	t_fd	*here_new;
	int		here_flg;

	here_flg = false;
	while (word_list != NULL && word_list->flag != heredoc_file)
		word_list = word_list->next;
	if (new_here_node(&here_node, word_list->word,env_list) == FAILURE)
		return (FAILURE);
	*fd_list = here_node;
	word_list = word_list->next;
	while (word_list != NULL)
	{
		if (word_list != NULL && word_list->flag == pipe_char)
			word_list = word_list->next;
		if (here_flg == false && find_heredoc_to_pipe(&word_list) == true)
		{
			here_flg = true;
			if (new_here_node(&here_new, word_list->word,env_list) == FAILURE)
				return (FAILURE);
			here_node->next = here_new;
			here_node = here_new;
		}
		if (here_flg == true && find_heredoc_to_pipe(&word_list) == true
			&& change_here_file(&here_node, word_list->word,
				env_list) == FAILURE)
			return (FAILURE);
		if (here_flg == true && find_heredoc_to_pipe(&word_list) == false)
			here_flg = false;
		word_list = word_list->next;
	}
	return (SUCCESS);
}
