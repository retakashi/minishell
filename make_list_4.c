/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:58:42 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/02 10:35:02 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_word_list	*argument_flag(t_word_list *string)
{
	t_word_list	*tmp;

	tmp = string;
	while (tmp != NULL)
	{
		tmp->flag = 0;
		tmp = tmp->next;
	}
	tmp = string;
	while (tmp != NULL)
	{
		if (tmp->word != NULL && (tmp->word[0] == '"' || tmp->word[0] == '\''))
			tmp->flag = 3;
		tmp = tmp->next;
	}
	tmp = string;
	return (string);
}
