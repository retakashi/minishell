/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 17:49:00 by reira             #+#    #+#             */
/*   Updated: 2023/07/24 21:49:28 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	add_new_fd_node(t_fd **fd_list,
						int i)
{
	t_fd	*node;
	t_fd	*head;

	head = *fd_list;
	node = malloc(sizeof(t_fd));
	if (node == NULL)
		put_error_exit("failed to new_fd_node");
	node->in_fd = STDIN_FILENO;
	node->out_fd = STDOUT_FILENO;
	node->here_file_name = NULL;
	node->pipe_cnt = i;
	node->next = NULL;
	while ((*fd_list)->next != NULL)
		*fd_list = (*fd_list)->next;
	(*fd_list)->next = node;
	*fd_list = head;
}

void	update_fd_node(t_fd **fd_list, int i, int *here_flg)
{
	t_fd	*head;

	*here_flg = true;
	head = *fd_list;
	while (*fd_list != NULL && (*fd_list)->pipe_cnt == 0)
		*fd_list = (*fd_list)->next;
	(*fd_list)->pipe_cnt = i;
	*fd_list = head;
}

bool	find_heredoc_to_pipe(t_word_list *word_list)
{
	while (word_list != NULL && word_list->flag != pipe_char)
	{
		if (word_list->flag == heredoc_file)
			return (true);
		word_list = word_list->next;
	}
	return (false);
}

void	get_fd_list(t_word_list *word_list, t_fd **fd_list,
		t_env_list **env_list, int pipe_cnt)
{
	int		i;
	int		here_flg;

	if (*fd_list == NULL)
		new_fd_node(word_list, fd_list, env_list, 0);
	i = 1;
	while (i < pipe_cnt)
	{
		here_flg = false;
		while (word_list != NULL && word_list->flag != pipe_char)
		{
			if (word_list != NULL && word_list->flag == heredoc)
				update_fd_node(fd_list, i, &here_flg);
			word_list = word_list->next;
		}
		if (here_flg == false)
			add_new_fd_node(fd_list, i);
		if (word_list != NULL && word_list->flag == pipe_char)
			word_list = word_list->next;
		i++;
	}
}
