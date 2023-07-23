/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:23:36 by reira             #+#    #+#             */
/*   Updated: 2023/07/23 03:13:24 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	new_word_node(t_word_list **node, char *argv)
{
	*node = malloc(sizeof(t_word_list));
	(*node)->next = NULL;
	(*node)->flag = arguments;
	if (ft_strchr(argv, '<'))
		(*node)->flag = input;
	else if (ft_strchr(argv, '>'))
		(*node)->flag = output;
	else if (!ft_strncmp(argv, ">>", 3))
		(*node)->flag = append;
	else if (!ft_strncmp(argv, "<<", 3))
		(*node)->flag = heredoc;
	(*node)->word = ft_strdup(argv);
}

void	get_word_list(t_word_list **head, char *line)
{
	t_word_list	*new;
	t_word_list	*node;
	size_t		i;
	char		**argv;

	i = 0;
	argv = ft_split(line, ' ');
	new_word_node(&node, argv[i]);
	i++;
	*head = node;
	while (argv[i] != NULL)
	{
		new_word_node(&new, argv[i]);
		if(node->flag==output)
		new->flag=output_file;
		node->next = new;
		node = new;
		i++;
	}
	i = 0;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
