/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 00:16:35 by reira             #+#    #+#             */
/*   Updated: 2023/07/28 18:42:28 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

bool	search_env_name_advance_list(char *str, t_env_list **env_list)
{
	size_t		str_name;
	size_t		env_name;
	t_env_list	*prev;

	if (*env_list == NULL)
		return (false);
	str_name = get_name_len(str);
	env_name = ft_strlen((*env_list)->env_name);
	while (*env_list != NULL)
	{
		prev = *env_list;
		if (str_name == env_name && ft_strncmp(str, (*env_list)->env_name,
				str_name) == 0)
			return (true);
		*env_list = (*env_list)->next;
	}
	*env_list = prev;
	return (false);
}

static int	add_env_list(t_env_list **env_list, char *str)
{
	t_env_list	*new;

	new = NULL;
	if (new_env_node(&new, str) == FAILURE)
		return (FAILURE);
	if (*env_list == NULL)
		*env_list = new;
	else
		(*env_list)->next = new;
	return (SUCCESS);
}

static int	update_env_str(t_env_list **env_list, char *str)
{
	size_t	name_len;

	if (!ft_strchr(str, '='))
		return (SUCCESS);
	name_len = get_name_len(str);
	free((*env_list)->env_str);
	(*env_list)->env_str = ft_strdup(&str[name_len + 1]);
	if ((*env_list)->env_str == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	export_cmd(t_word_list *word_list, t_env_list **env_list, int fd,
		int *exit_error_flg)
{
	t_env_list	*head;

	if (word_list->next == NULL || (word_list->next->flag != arguments
			&& word_list->next->flag != option))
		return (export_nooption(env_list, fd));
	word_list = word_list->next;
	head = *env_list;
	while (word_list != NULL && word_list->flag == arguments)
	{
		*env_list = head;
		if (search_env_name_advance_list(word_list->word, env_list) == true
			&& update_env_str(env_list, word_list->word) == FAILURE)
			return (change_exit_error_flg(exit_error_flg));
		if (search_env_name_advance_list(word_list->word, env_list) == false
			&& add_env_list(env_list, word_list->word) == FAILURE)
			return (change_exit_error_flg(exit_error_flg));
		word_list = word_list->next;
	}
	*env_list = head;
	return (SUCCESS);
}
