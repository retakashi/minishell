/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 00:52:59 by reira             #+#    #+#             */
/*   Updated: 2023/07/29 00:54:21 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

void	write_env_exportver(t_env_list *env_list, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(env_list->env_name, fd);
	if (env_list->env_str != NULL)
	{
		ft_putstr_fd("=", fd);
		ft_putstr_fd("\"", fd);
		ft_putstr_fd(env_list->env_str, fd);
		ft_putstr_fd("\"", fd);
	}
	ft_putstr_fd("\n", fd);
}

bool	search_env_name_advance_env_list(char *str, t_env_list **env_list)
{
	size_t		str_name;
	size_t		env_name;
	t_env_list	*prev;

	if (*env_list == NULL || (*env_list)->env_name == NULL)
		return (false);
	str_name = get_name_len(str);
	if ((*env_list)->env_str != NULL)
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
