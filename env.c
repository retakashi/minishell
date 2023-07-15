/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:06:01 by reira             #+#    #+#             */
/*   Updated: 2023/07/15 17:30:33 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

static void	write_env(t_env_list *env_list)
{
	t_env_list	*node;

	ft_getenvp("PATH", &node);
	if (node == NULL)
		perror_exit(NULL, ENV_ERROR);
	while (env_list != NULL)
	{
		if (env_list->env_str != NULL && env_list->shell_variable == false)
		{
			write(1, env_list->env_name, ft_strlen(env_list->env_name));
			write(1, "=", 1);
			write(1, env_list->env_str, ft_strlen(env_list->env_str));
			write(1, "\n", 1);
		}
		env_list = env_list->next;
	}
}

void	env_cmd(t_word_list **word_list, t_env_list *env_list)
{
	write_env(env_list);
	while (*word_list != NULL && (*word_list)->flag != pipe_char)
		*word_list = (*word_list)->next;
}
