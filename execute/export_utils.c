/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 00:52:59 by reira             #+#    #+#             */
/*   Updated: 2023/08/11 20:12:28 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute_cmd.h"

void	write_env_exportver(t_env_list *env_list, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(env_list->env_name, fd);
	if (env_list->env_value != NULL)
	{
		ft_putstr_fd("=", fd);
		ft_putstr_fd("\"", fd);
		ft_putstr_fd(env_list->env_value, fd);
		ft_putstr_fd("\"", fd);
	}
	ft_putstr_fd("\n", fd);
}

bool	search_env_name_advance_env_list(char *word, t_env_list **env_list)
{
	size_t		word_name;
	size_t		env_name;
	t_env_list	*prev;

	word_name = get_name_len(word);
	while (*env_list != NULL)
	{
		env_name = ft_strlen((*env_list)->env_name);
		prev = *env_list;
		if (word_name == env_name && ft_strncmp(word, (*env_list)->env_name,
				word_name) == 0)
			return (true);
		*env_list = (*env_list)->next;
	}
	*env_list = prev;
	return (false);
}
