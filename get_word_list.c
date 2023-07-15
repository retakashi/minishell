/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:23:36 by reira             #+#    #+#             */
/*   Updated: 2023/07/15 16:32:49 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	new_word_list(t_word_list **node, char *argv)
{
	*node = malloc(sizeof(t_word_list));
	(*node)->next = NULL;
	if (ft_strchr(argv, '<'))
		(*node)->flag = less;
	else if (ft_strchr(argv, '>'))
		(*node)->flag = great;
	else if (ft_strncmp(argv, ">>", 2))
		(*node)->flag = great_great;
	else if (ft_strncmp(argv, "<<", 2))
		(*node)->flag = less_less;
	else
		(*node)->flag = arguments;
	(*node)->word = ft_strdup(argv);
}

void	get_word_list(t_word_list **head, char **argv)
{
	t_word_list *new;
	t_word_list *node;
	size_t i;

	new_word_node(&node,argv[1]);
	g_shell_struct = node;
	*head = node;
	i = 2;
	while (argv[i] != NULL)
	{
		new_word_node(&new, argv[i]);
		node->next = new;
		node = new;
		i++;
	}
}
