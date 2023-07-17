/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:39:25 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/17 09:45:31 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	parse_line(char *line)
{
	t_word_list	*string;
	t_word_list	*tmp;

	if (*line == '#' || line[strlen(line) - 1] == '|')
	{
		printf(" comment out or End with pipe!\n");
		return ;
	}
	string = make_list(line);
	tmp = string;
	printf( "\n ---------------       ----------------\n");
	print_words(tmp);
	return ;
}

void	print_words(t_word_list *string)
{
	while (string != NULL)
	{
		printf("string->word = %s \n", string->word);
		string = string->next;
	}
	return ;
}