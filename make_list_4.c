/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:58:42 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/17 13:54:58 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_word_list	*divide_quotes2(t_word_list *string)
{
	t_word_list	*tmp;
	t_word_list	*tmp2;
	int			i;

	tmp = string;
	i = 0;
	if (*string->word != NULL)
		string->word++;
	while(*string->word != NULL)
	{
		while()
	}
}

t_word_list	*divide_quotes(t_word_list *string)
{
	if ((string->word[0] == '"' && string->word[ft_strlen(string->word) - 1] != '"') ||
		(string->word[0] == '\'' && string->word[ft_strlen(string->word) - 1] != '\''))
		divide_quotes2(string);
	return (string);
}

t_word_list	*argument_flag(t_word_list *string)
{
	t_word_list	*tmp;

	tmp = string;
	while (tmp != NULL)
	{
		string = divide_quotes(string);
		if (tmp->word != NULL && (tmp->word[0] == '"' || tmp->word[0] == '\''))
			tmp->flag = 3;
		if (tmp->flag == 3)
			printf("%s is an argument\n", tmp->word);
		tmp = tmp->next;
	}
	// string = tmp;
	printf("finished\n");
	return (string);
}
