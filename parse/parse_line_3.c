/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:39:25 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/17 09:47:25 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	t_word_list	*split_quotes(t_word_list *string)
{
	char	*str;

	if (string->word[0] == '\'')
	{
		str = string->word;
		string->word = ft_strtrim(string->word, "'");
		free(str);
	}
	else if (string->word[0] == '"')
	{
		str = string->word;
		string->word = ft_strtrim(string->word, "\"");
		free(str);
	}
	return (string);
}

static	t_word_list	*trim_quotes2(t_word_list *string)
{
	int			i;

	i = 0;
	while (string->word[i] != '\'' && string->word[i] != '"'
		&& string->word[i] != '\0')
		i++;
	if (string->word[i] == '\0' || ft_strlen(string->word) == 1)
		return (string);
	if ((string->word[0] == '\''
			&& string->word[ft_strlen(string->word) - 1] == '\'')
		|| (string->word[0] == '"'
			&& string->word[ft_strlen(string->word) - 1] == '"'))
		return (split_quotes(string));
	return (string);
}

t_word_list	*trim_quotes(t_word_list *string)
{
	t_word_list	*tmp;

	tmp = string;
	while (string)
	{
		if (string->flag == 3)
			string = trim_quotes2(string);
		string = string->next;
	}
	return (tmp);
}
