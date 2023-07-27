/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 10:22:05 by reira             #+#    #+#             */
/*   Updated: 2023/07/27 20:18:35 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "execve_cmd.h"

void	free_here_list(t_here_list **list)
{
	t_here_list	*node;
	t_here_list	*next;

	if (*list == NULL)
		return ;
	node = *list;
	next = NULL;
	while (node != NULL)
	{
		next = node->next;
		if (node->here_file_name != NULL)
			free(node->here_file_name);
		free(node);
		node = next;
	}
	*list = NULL;
}

void	free_word_list(t_word_list **list)
{
	t_word_list	*node;
	t_word_list	*next;

	if (*list == NULL)
		return ;
	node = *list;
	while (node != NULL)
	{
		next = node->next;
		free(node->word);
		free(node);
		node = next;
	}
	*list = NULL;
}

void	free_env_list(t_env_list **list)
{
	t_env_list	*node;
	t_env_list	*next;

	if (*list == NULL)
		return ;
	node = *list;
	while (node != NULL)
	{
		next = node->next;
		free(node->env_name);
		free(node->env_str);
		free(node);
		node = next;
	}
	*list = NULL;
}
