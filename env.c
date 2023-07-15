/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:06:01 by reira             #+#    #+#             */
/*   Updated: 2023/07/16 01:24:29 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	env_cmd(t_word_list **word_list,t_env_list *env_list)
{
	t_env_list	*tmp;

	ft_get_env("PATH",env_list &tmp);
	if (tmp == NULL)
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
	while (*word_list != NULL && (*word_list)->flag != pipe_char)
		*word_list = (*word_list)->next;
}
