/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:39:25 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/23 18:54:52 by sraza            ###   ########.fr       */
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
	t_word_list	*tmp;

	if (check_sp(line))
		return ;
	/*ここに環境変装の展開を入れるgetenvにするかリスト型で持つかあとで決める
		mallocして文字列の長さを変えていくようにする
	*/
	string = make_list(line);
	tmp = string;
	printf( "\n ---------------       ----------------\n");
	print_words(tmp);
	printf( "\n ++++++++++++++       +++++++++++++++\n");
	string = set_flags(string);
	print_words(tmp);
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