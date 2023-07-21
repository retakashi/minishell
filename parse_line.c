/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:39:25 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/21 10:58:27 by razasharuku      ###   ########.fr       */
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

t_word_list	*set_flags(t_word_list	*string)
{
	t_word_list	*tmp;

	tmp = string;
	while (tmp != NULL)
	{
		tmp->flag = is_meta(tmp->word);
		if (tmp->flag == 0 && tmp->word[0] == '-')
			tmp->flag = 2;
		tmp = tmp->next;
	}
	return (string);
}

void	parse_line(char *line)
{
	t_word_list	*string;

	if (check_sp(line))
		return ;
	string = make_list(line);
	printf( "\n ---------------       ----------------\n");
	print_words(string);
	printf( "\n ---------------       ----------------\n");
	string = set_flags(string);
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