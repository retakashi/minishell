/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:39:25 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/10 17:23:03 by sraza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	parse_line(const char *line)
{
	char		**line2;
	t_word_list	*string;


	if (*line == '#' || line[strlen(line) - 1] == '|')
	{
		printf(" comment out or End with pipe!\n");
		return ;
	}
	line2 = ft_split(line, ' ');
	string = make_list(line2);
	ft_free_line2(line2);
	while (string != NULL)
	{
		printf("string->word = %s \n", string->word);
		string = string->next;
	}
	return ;
}