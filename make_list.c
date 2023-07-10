/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:11:24 by sraza             #+#    #+#             */
/*   Updated: 2023/07/10 17:11:51 by sraza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/*新しいリストを作る→次のノードの指す場所はNUll埋めする*/
t_word_list	*ft_newlst(char *content)
{
	t_word_list	*new;

	new = malloc(sizeof(t_word_list));
	if (new == NULL)
		return (NULL);
	new->word = ft_strdup(content);
	new->next = NULL;
	return (new);
}

/*Listというスプリットされた配列を線形リストに変形する関数*/
t_word_list *make_list(char **list)
{
	int			i;
	t_word_list	*string;
	t_word_list	*new;
	t_word_list	*tmp;

	i = 1;
	string = ft_newlst(list[0]);
	tmp = string;
	while (list[i] != NULL)
	{
		new = ft_newlst(list[i]);
		new->flag = i;
		string->next = new;
		string = string->next;
		i++;
	}
	return (tmp);
}
