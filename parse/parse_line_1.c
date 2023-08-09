/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:39:25 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/09 17:38:54 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	check_sp(char *line)
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

t_word_list	*parse_line(char *line)
{
	t_word_list	*string;
	t_word_list	*tmp;

	if (line == NULL)
		return (NULL);
	if (check_sp(line))
		return (NULL);
	string = make_list(line);
	tmp = string;
	string = argument_flag(string);
	string = set_flags(string);
	print_words(string);
	string = tmp;
	return (tmp);
}

void	print_words(t_word_list *string)
{
	while (string != NULL)
	{
		printf("string->word = %s , string->flag = %i \n",
			string->word, string->flag);
		string = string->next;
	}
	return ;
}
