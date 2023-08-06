/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:44:21 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/04 18:33:42 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	len_of_string(t_word_list *string)
{
	int	i;

	i = 0;
	while (string)
	{
		i++;
		string = string->next;
	}
	return (i);
}

void	one_string(t_word_list *string)
{
	if (is_just_meta(string->word) == 5)
		printf("syntax error near unexpected token '%s'\n", string->word);
	else
		printf("syntax error near unexpected token `newline'\n");
	// exit(0);
}

void	command_error(t_word_list *string)
{
	if (string->next != NULL)
	{
		if (string->flag == 1 && (string->next->flag
			> 5 && string->next->flag < 10))
			printf("syntax error near unexpected token `newline'\n");
		return ;
	}
	return ;
}

void	redirect_error(t_word_list *string)
{
	if (string->next != NULL)
	{
		if (string->flag > 5 && string->flag < 10)
			if (string->next->flag > 5 && string->next->flag < 10)
				printf("syntax error near unexpected token '%s'\n", string->word);
		return ;
	}
	return ;
}

void	last_error(t_word_list *string)
{
	if (string->next != NULL)
	{
		if (string->flag > 5 && string->flag < 10)
			printf("syntax error near unexpected token `newline'\n");
		return ;
	}
	return ;
}

t_word_list	*check_error(t_word_list *string)
{
	int			s_len;
	t_word_list	*tmp;

	tmp = string;
	s_len = len_of_string(string);
	if (s_len == 1 && string->flag != 0)
		one_string(string);
	while (string)
	{
		command_error(string);
		redirect_error(string);
		if (string->next == NULL)
			last_error(string);
		string = string->next;
	}
	return (tmp);
}