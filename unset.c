/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:49:46 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/30 21:41:15 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

static void	get_prev_node(t_env_list **env_list, t_word_list *word_list)
{
	t_env_list	*prev;

	prev = *env_list;
	while (*env_list != NULL && ft_strcmp((*env_list)->env_name,
			word_list->word) != 0)
	{
		prev = *env_list;
		*env_list = (*env_list)->next;
	}
	*env_list = prev;
}

bool	search_env_name(t_word_list *word_list, t_env_list *env_list)
{
	while (env_list != NULL && ft_strcmp(env_list->env_name,
			word_list->word) != 0)
		env_list = env_list->next;
	if (env_list == NULL)
		return (false);
	return (true);
}

static void	remove_node(t_word_list *remove_word, t_env_list **env_list,
		t_env_list **head)
{
	t_env_list	*remove_node;

	if (ft_strcmp((*head)->env_name, remove_word->word) == 0)
	{
		remove_node = *env_list;
		*head = (*env_list)->next;
	}
	else
	{
		get_prev_node(env_list, remove_word);
		remove_node = (*env_list)->next;
		(*env_list)->next = remove_node->next;
	}
	free(remove_node->env_name);
	free(remove_node->env_str);
	free(remove_node);
}

void	unset_cmd(t_word_list *word_list, t_env_list **env_list)
{
	t_env_list	*head;

	word_list = word_list->next;
	if (*env_list == NULL || (*env_list)->env_name == NULL || word_list == NULL)
		return ;
	head = *env_list;
	while (word_list != NULL && word_list->flag == arguments)
	{
		*env_list = head;
		if (search_env_name(word_list, *env_list) == true)
			remove_node(word_list, env_list, &head);
		word_list = word_list->next;
	}
	*env_list = head;
}
