/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:23:36 by reira             #+#    #+#             */
/*   Updated: 2023/07/18 21:30:19 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

extern t_shell			*g_shell_struct;

void	new_word_node(t_word_list **node, char *argv)
{
	*node = malloc(sizeof(t_word_list));
	(*node)->next = NULL;
	if (ft_strchr(argv, '<'))
		(*node)->flag = less;
	else if (ft_strchr(argv, '>'))
		(*node)->flag = great;
	else if (!ft_strncmp(argv, ">>", 3))
		(*node)->flag = great_great;
	else if (!ft_strncmp(argv, "<<", 3))
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

	i = 0;
	new_word_node(&node,argv[i]);
	i++;
	*head = node;
	while (argv[i] != NULL)
	{
		new_word_node(&new, argv[i]);
		node->next = new;
		node = new;
		i++;
	}
}
