/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 10:22:05 by reira             #+#    #+#             */
/*   Updated: 2023/07/30 21:46:04 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

void	free_word_list(t_word_list **list)
{
	t_word_list	*node;
	t_word_list	*next;

	if (list == NULL)
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

	if (list == NULL)
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

void	free_here_list(t_here_list **list)
{
	t_here_list	*node;
	t_here_list	*next;

	if (list == NULL)
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

void	free_all_list(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list)
{
	free_word_list(word_list);
	free_env_list(env_list);
	free_here_list(here_list);
}

void	free_int_2darr(int ***arr, int cnt)
{
	int	i;

	i = 0;
	while (i < cnt)
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	free_char_2darr(char ***arr)
{
	size_t	i;

	i = 0;
	while ((*arr)[i] != NULL)
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
}
