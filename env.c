/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:06:01 by reira             #+#    #+#             */
/*   Updated: 2023/07/23 22:01:03 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	env_cmd(t_word_list **word_list, t_env_list **env_list, int fd)
{
	t_env_list	*tmp;
	t_env_list	*head;

	tmp = NULL;
	ft_get_env("PATH", env_list, &tmp);
	if (tmp == NULL)
		return (put_error("env: No such file or directory\n", NO_ERRNO,
				env_list));
	head = *env_list;
	while (*env_list != NULL)
	{
		if ((*env_list)->env_str != NULL)
		{
			ft_putstr_fd((*env_list)->env_name, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd((*env_list)->env_str, fd);
			ft_putstr_fd("\n", fd);
		}
		*env_list = (*env_list)->next;
	}
	*env_list = head;
	return (SUCCESS);
}
