/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:06:01 by reira             #+#    #+#             */
/*   Updated: 2023/07/06 16:43:22 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

//argv[0]->envp
//argv[1]->option

t_envp		*g_envp_list;

static void	write_envp(void)
{
	t_envp	*head;
	t_envp	*node;

	node = NULL;
	ft_getenvp("PATH", &node);
	if (node == NULL || node->envp_str == NULL)
		perror_free_2d_arr_exit(NULL, NULL, NULL, ENV_ERROR);
	head = g_envp_list;
	while (g_envp_list != NULL)
	{
		if (g_envp_list->envp_str != NULL)
		{
			write(1, g_envp_list->envp_name, ft_strlen(g_envp_list->envp_name));
			write(1, "=", 1);
			write(1, g_envp_list->envp_str, ft_strlen(g_envp_list->envp_str));
			write(1, "\n", 1);
		}
		g_envp_list = g_envp_list->next;
	}
	g_envp_list = head;
}

void	env_cmd(t_word_list **head)
{
	write_envp();
	while (*head != NULL && (*head)->flag != pipe_char)
		*head = (*head)->next;
}
