/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 00:16:35 by reira             #+#    #+#             */
/*   Updated: 2023/07/16 01:07:32 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

bool	search_env_name(char *str, t_env_list **env_list)
{
	size_t	str_name;
	size_t	env_name;

	if (*env_list == NULL)
		return (false);
	str_name = get_name_len(str);
	env_name = ft_strlen((*env_list)->env_name);
	while ((*env_list)->next != NULL && str_name == env_name && ft_strncmp(str,
			(*env_list)->env_name, str_name) == 0)
		*env_list = (*env_list)->next;
	if ((*env_list)->next == NULL && !(str_name == env_name && ft_strncmp(str,
				(*env_list)->env_name, str_name) == 0))
		return (false);
	return (true);
}

void	add_env_list(t_env_list **env_list, char *str)
{
	t_env_list	*new;

	new = NULL;
	new_node(&new, str);
	(*env_list)->next = new;
}

void	update_env_str(t_env_list **env_list, char *str)
{
	size_t	name_len;

	if (!ft_strchr(str, '='))
		return ;
	name_len = get_name_len(str);
	free((*env_list)->env_str);
	(*env_list)->env_str = ft_strdup(&str[name_len + 1]);
	if ((*env_list)->env_str == NULL)
		perror_exit("ft_strdup", 0);
}

void	export_cmd(t_word_list **word_list, t_env_list **env_list)
{
	t_env_list	*head;

	head = *env_list;
	if ((*word_list)->next == NULL)
		export_nooption(*env_list);
	else
	{
		*word_list = (*word_list)->next;
		while (*word_list != NULL && (*word_list)->flag != arguments)
		{
			if (search_env_name((*word_list)->word, env_list) == true)
				update_env_str(env_list, (*word_list)->word);
			else
				add_env_list(env_list, (*word_list)->word);
			*word_list = (*word_list)->next;
		}
		// export_nooption();
	}
	*env_list=head;
}
