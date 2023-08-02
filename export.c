/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 00:16:35 by reira             #+#    #+#             */
/*   Updated: 2023/08/02 22:26:35 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "libft/libft.h"

static int	add_env_list(t_env_list **env_list, char *str)
{
	t_env_list	*new;

	new = NULL;
	if (new_env_node(&new, str) == FAILURE)
		return (ft_perror("new_env_node"));
	if (*env_list == NULL)
		*env_list = new;
	else
		(*env_list)->next = new;
	return (SUCCESS);
}

static int	update_env_value(t_env_list **env_list, char *word)
{
	size_t	name_len;

	if (!ft_strchr(word, '='))
		return (SUCCESS);
	name_len = get_name_len(word);
	free((*env_list)->env_value);
	(*env_list)->env_value = ft_strdup(&word[name_len + 1]);
	if ((*env_list)->env_value == NULL)
		return (ft_perror("ft_strdup"));
	return (SUCCESS);
}

static bool	is_valid_identifier(char *str)
{
	size_t	i;

	if (str != NULL && !ft_isalpha(str[0]))
		return (false);
	i = 0;
	if (ft_strchr(str, '='))
	{
		while (str[i] != '\0' && str[i] != '=')
		{
			if (str[i] == ' ' || str[i] == '\t')
				return (false);
			i++;
		}
	}
	return (true);
}

int	export_cmd(t_word_list *word_list, t_env_list **env_list, int fd,
		int *exit_flg)
{
	t_env_list	*head;

	if (word_list->next == NULL || (word_list->next->flag != arguments
			&& word_list->next->flag != option))
		return (export_nooption(env_list, fd));
	word_list = word_list->next;
	head = *env_list;
	while (word_list != NULL && word_list->flag == arguments)
	{
		if (is_valid_identifier(word_list->word) == false)
			return (export_error_update_exit_status(word_list->word, env_list));
		if (search_env_name_advance_env_list(word_list->word, env_list) == true
			&& update_env_value(env_list, word_list->word) == FAILURE)
			return (change_exit_flg(exit_flg));
		if (search_env_name_advance_env_list(word_list->word, env_list) == false
			&& add_env_list(env_list, word_list->word) == FAILURE)
			return (change_exit_flg(exit_flg));
		word_list = word_list->next;
	}
	*env_list = head;
	return (SUCCESS);
}
