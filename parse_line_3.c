/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:44:21 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/04 18:11:54 by razasharuku      ###   ########.fr       */
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


t_word_list	*check_error(t_word_list *string)
{
	int	s_len; 

	s_len = len_of_string(string);
	if (s_len == 1 && is_just_meta(string->word) != 0)
		one_string(string);
	// while (string)
	// {
	// 	command_
	// }

	return (string);
}