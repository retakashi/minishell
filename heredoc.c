/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:17:41 by reira             #+#    #+#             */
/*   Updated: 2023/07/25 23:21:35 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

static int	new_here_node(t_fd_list **new, char *eof, t_env_list **env_list)
{
	char	*name;

	new_fd_node(new, 0);
	name = get_file_name(0);
	if (name == NULL)
		put_error_exit("failed to get_name_len");
	(*new)->here_file_name = ft_strdup(name);
	if (name == NULL)
	{
		free(name);
		put_error_exit("failed to ft_strdup");
	}
	free(name);
	if (get_heredoc_file(new, eof, env_list) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	update_here_file(t_fd_list **node, char *eof, t_env_list **env_list)
{
	char	*new_name;

	if (unlink((*node)->here_file_name) < 0)
		return (put_cd_error_update_exit_status("unlink", env_list));
	free((*node)->here_file_name);
	new_name = get_file_name(1);
	if (new_name == NULL)
		put_error_exit("failed to get_name_len");
	(*node)->here_file_name = ft_strdup(new_name);
	if (new_name == NULL)
	{
		free(new_name);
		put_error_exit("failed to ft_strdup");
	}
	free(new_name);
	if (get_heredoc_file(node, eof, env_list) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	create_head_node(t_fd_list **node, t_word_list **word_list,
		t_env_list **env_list, int *here_flg)
{
	while (*word_list != NULL && (*word_list)->flag != eof_num)
		*word_list = (*word_list)->next;
	if (new_here_node(node, (*word_list)->word, env_list) == FAILURE)
		return (FAILURE);
	*word_list = (*word_list)->next;
	*here_flg = true;
	return (SUCCESS);
}

static int	create_or_update_here_node(t_word_list **word_list, int *here_flg)
{
	while (*word_list != NULL && (*word_list)->flag != pipe_char)
	{
		if ((*word_list)->flag == eof_num && *here_flg == false)
		{
			*here_flg = true;
			return (CREATE);
		}
		if ((*word_list)->flag == eof_num && *here_flg == true)
			return (UPDATE);
		*word_list = (*word_list)->next;
	}
	*here_flg = false;
	return (false);
}

int	main_heredoc(t_word_list *word_list, t_fd_list **fd_list,
		t_env_list **env_list)
{
	t_fd_list	*new;
	t_fd_list	*node;
	int			here_flg;

	if (create_head_node(&node, &word_list, env_list, &here_flg) == FAILURE)
		return (FAILURE);
	*fd_list = node;
	while (word_list != NULL)
	{
		if (create_or_update_here_node(&word_list, &here_flg) == CREATE)
		{
			if (new_here_node(&new, word_list->word, env_list) == FAILURE)
				return (FAILURE);
			node->next = new;
			node = new;
		}
		if (create_or_update_here_node(&word_list, &here_flg) == UPDATE
			&& update_here_file(&node, word_list->word, env_list) == FAILURE)
			return (FAILURE);
		if (word_list != NULL)
			word_list = word_list->next;
	}
	return (SUCCESS);
}
