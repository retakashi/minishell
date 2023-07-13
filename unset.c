/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:49:46 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/07 19:30:17 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

//argv[0]->unset
//argv[1]->variable

t_envp	*g_envp_list;

void	remove_node(t_envp **head, t_envp *node)
{
	t_envp	*prev;

	if (*head == node)
		*head = g_envp_list->next;
	else
	{
		prev = g_envp_list;
		while (g_envp_list != NULL)
		{
			if (!ft_strcmp(node->envp_name, g_envp_list->envp_name))
			{
				prev->next = g_envp_list->next;
				break ;
			}
			prev = g_envp_list;
			g_envp_list = g_envp_list->next;
		}
	}
	free(g_envp_list->envp_name);
	free(g_envp_list->envp_str);
	free(g_envp_list);
}

void	unset_cmd(char **argv)
{
	t_envp	*node;
	t_envp	*head;

	if (argv[1] == NULL)
		return ;
	node = NULL;
	if (search_same_name(argv[1], &node) == FALSE)
		return ;
	head = g_envp_list;
	remove_node(&head, node);
	g_envp_list = head;
	// export_nooption();
}
