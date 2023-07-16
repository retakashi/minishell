/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:11:24 by sraza             #+#    #+#             */
/*   Updated: 2023/07/16 17:20:12 by sraza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_word_list	*make_list(char *line)
{
	int			i;
	t_word_list	*string;
	t_word_list	*tmp;

	i = 0;
	//make first_list
	while (*line == ' ' || *line == '\t')
		line++;
	while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
		i++;
	string = creat_list(line, i);
	line += i;
	while (*line == ' ' || *line == '\t')
		line++;
	tmp = string;
	i = 0;
	//make intermediate_list
	while (*line != '\0' && line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '\t')
		{
			string = sp_sprt(&line, string, i);
			while (*line == ' ' || *line == '\t')
				line++;
			i = -1;
		}
		i++;
	}
	//make last_list
	while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
		i++;
	if (i != 0)
	{
		string->next = creat_list(line, i);
		string->next->next = NULL;
	}
	string = tmp;
	printf( "\n ----------  after meta  -------\n");
	string = find_meta(string);
	print_words(string);
	return (string);
}
