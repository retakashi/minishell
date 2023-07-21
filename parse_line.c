/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:39:25 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/19 14:16:14 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	check_sp(char *line)
{
	int	i;
	int	len;

	len = ft_strlen(line);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (i == len)
		return (1);
	return (0);
}

void	parse_line(char *line)
{
	t_word_list	*string;

	if (check_sp(line))
		return ;
	if (*line == '#' || line[strlen(line) - 1] == '|')
	{
		printf(" comment out or End with pipe!\n");
		return ;
	}
	string = make_list(line);
	printf( "\n ---------------       ----------------\n");
	print_words(string);
	return ;
}

void	print_words(t_word_list *string)
{
	while (string != NULL)
	{
		printf("string->word = %s , string->flag = %i \n", string->word, string->flag);
		string = string->next;
	}
	return ;
}