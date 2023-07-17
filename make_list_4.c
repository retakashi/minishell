/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:58:42 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/17 20:15:46 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

// t_word_list	*divide_quotes2(t_word_list *string, int c)
// {
// 	t_word_list	*tmp;
// 	t_word_list	*tmp2;
// 	t_word_list	*new;
// 	int			i;

// 	tmp = string;
// 	tmp2 = string->next;
// 	i = 1;
// 	while (string->word[i] != '\0')
// 	{
// 		while (string->word[i] != c)
// 			i++;
// 		if (string->word[i] == c)
// 		{
// 			new = creat_list(string->word, i);
// 			string->next = new;
// 			string = string->next;
// 			string->next = tmp2;
// 			printf("its come here \"zone\"!!");
// 			return (tmp);
// 		}
// 	}
// 	return (string);
// }

// t_word_list	*divide_quotes(t_word_list *string)
// {
// 	if (string->word[0] == '"' && string->word[ft_strlen(string->word) - 1] != '"')
// 		string = divide_quotes2(string, '"');
// 	else if (string->word[0] == '\'' && string->word[ft_strlen(string->word) - 1] != '\'')
// 		string = divide_quotes2(string, '\'');
// 	return (string);
// }

t_word_list	*argument_flag(t_word_list *string)
{
	t_word_list	*tmp;

	tmp = string;
	while (tmp != NULL)
	{
		// string = divide_quotes(string);
		if (tmp->word != NULL && (tmp->word[0] == '"' || tmp->word[0] == '\''))
			tmp->flag = 3;
		if (tmp->flag == 3)
			printf("%s is an argument\n", tmp->word);
		tmp = tmp->next;
	}
	// string = tmp;
	return (string);
}
