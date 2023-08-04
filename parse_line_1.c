/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:44:21 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/04 12:54:59 by sraza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_word_list	*find_syntax_er(t_word_list	*string)
{
	if (string->word[0] == pipe_char)
		printf("syntax error near unexpected token '%c'", string->word[0]);
	return (string);
}

t_word_list	*redirect_command(t_word_list *tmp)
{
	tmp->flag = is_just_meta(tmp->word);
	if (tmp->flag != 0)
		return (tmp);
	if (tmp->next != NULL)
		tmp->next->flag = tmp->flag + 5;
	if (tmp->next != NULL && tmp->next->next != NULL)
	{
		tmp = tmp->next->next;
		tmp->flag = 1;
	}
	return (tmp);
}

t_word_list	*set_flags_per_list(t_word_list	*tmp)
{
	if (tmp->flag == 5 && tmp->next != NULL)
	{
		if (is_just_meta(tmp->next->word) > 5
			&& is_just_meta(tmp->next->word) < 10)
		{
			tmp = tmp->next;
			tmp->flag = is_just_meta(tmp->word);
			tmp = redirect_command(tmp);
		}
		else
			tmp->next->flag = 1;
	}
	if (tmp->flag == 1 && tmp->next != NULL && tmp->next->word[0] == '-')
		tmp->next->flag = 2;
	if (tmp->flag == 1 && tmp->next != NULL && tmp->next->word[0] != '-'
		&& !(is_just_meta(tmp->next->word) > 3
			&& is_just_meta(tmp->next->word) < 15))
		tmp->next->flag = 3;
	if (tmp->flag > 5 && tmp->flag < 10 && tmp->next != NULL)
		tmp->next->flag = tmp->flag + 5;
	if (tmp->flag == 0)
		tmp->flag = 3;
	return (tmp);
}

t_word_list	*set_meta_flags(t_word_list	*string)
{
	t_word_list	*tmp;
	int			flag;

	tmp = string;
	while (string)
	{
		flag = is_just_meta(string->word);
		if (flag != 0)
			string->flag = flag;
		string = string->next;
	}
	return (tmp);
}

t_word_list	*set_flags(t_word_list	*string)
{
	t_word_list	*tmp;

	tmp = string;
	if (is_just_meta(tmp->word) == 0)
		tmp->flag = 1;
	else
		tmp->flag = is_just_meta(tmp->word);
	if (string->flag > 5 && string->flag < 10)
		tmp = redirect_command(tmp);
	string = find_syntax_er(string);
	while (tmp != NULL)
	{
		if (tmp->flag == 0)
		{
			if (is_just_meta(tmp->word) != 0)
				tmp->flag = is_just_meta(tmp->word);
		}
		tmp = set_flags_per_list(tmp);
		tmp = tmp->next;
	}
	string = set_meta_flags(string);
	return (string);
}
