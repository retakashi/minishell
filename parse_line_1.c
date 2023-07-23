/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:44:21 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/23 15:17:51 by sraza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_word_list	*find_syntax_er(t_word_list	*string)
{
	if (string->word[0] == pipe_char )
		printf("syntax error near unexpected token '%c'", string->word[0]);
	return (string);
}

t_word_list	*redirect_command(t_word_list *tmp)
{
	tmp->next->flag = tmp->flag + 5;
	tmp = tmp->next->next;
	tmp->flag = 1;
	tmp = tmp->next;
	return (tmp);
}

t_word_list	*set_flags(t_word_list	*string)
{
	t_word_list	*tmp;

	tmp = string;
	string = find_syntax_er(string);
	if (is_meta(tmp->word) == 0)
		tmp->flag = 1;
	else
		tmp->flag = is_meta(tmp->word);
	while (tmp != NULL)
	{
		if (string->flag > 5 && string->flag < 10)
			tmp = redirect_command(tmp);
		if (tmp->flag == 0)
		{
			if (is_meta(tmp->word) != 0)
				tmp->flag = is_meta(tmp->word);
		}
		if (tmp->flag == 1 && tmp->next->word[0] == '-')
			tmp->next->flag = 2;
		if (tmp->flag == 1 && tmp->next->word[0] != '-' &&
			!(is_meta(tmp->next->word) > 3 && is_meta(tmp->next->word) < 15))
			tmp->next->flag = 3;
		if (tmp->flag > 5 && tmp->flag < 10)
			tmp->next->flag = tmp->flag + 5;
		if (tmp->flag == 5)
		{
			if (is_meta(tmp->next->word) > 5 && is_meta(tmp->next->word) < 10)
				tmp = redirect_command(tmp);
			else
				tmp->next->flag = 1;
		}
		if (tmp->flag == 0)
			tmp->flag = 3;
		tmp = tmp->next;
	}
	return (string);
}
