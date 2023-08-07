/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 11:58:41 by sraza             #+#    #+#             */
/*   Updated: 2023/08/07 11:14:57 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static	int	is_just_str(t_word_list *string)
{
	int	i;

	i = 0;
	if (string->word[i] == '"')
	{
		i++;
		while (string->word[i] != '"' && string->word[i] != '\0')
			i++;
		if (string->word[i] == '"' && string->word[i + 1] == '\0')
			return (1);
	}
	if (string->word[i] == '\'')
	{
		i++;
		while (string->word[i] != '\'' && string->word[i] != '\0')
			i++;
		if (string->word[i] == '\'' && string->word[i + 1] == '\0')
			return (1);
	}
	while ((ft_isalnum(string->word[i]) || (is_include_meta(&string->word[i]))
			== 0) && string->word[i] != '\0')
		i++;
	if (string->word[i] == '\0')
		return (1);
	return (0);
}

static	int	len_of_str_meta(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			break ;
		i++;
	}
	return (i);
}

static	t_word_list	*divide_str_meta(t_word_list *string, t_word_list *tmp2)
{
	int			i;
	int			j;
	t_word_list	*new;
	char		*str;

	j = 0;
	i = len_of_str_meta(string->word);
	str = malloc(sizeof (char) * (i + 1));
	while (j < i)
	{
		str[j] = string->word[j];
		j++;
	}
	string->word = (string->word + i);
	new = ft_newlst(string->word);
	if (string->word == NULL)
		return (NULL);
	string->word = malloc(sizeof (char) * (i + 1));
	string->word = duplicate(string->word, str, i);
	string->next = new;
	new->next = tmp2;
	return (string);
}

static	t_word_list	*split_argument(t_word_list *string)
{
	if (is_just_meta(string->word) != 0)
		return (string);
	if (is_just_str(string) != 0)
		return (string);
	if (is_include_meta(string->word) != 0)
		return (divide_meta_str(string, is_include_meta(string->word)));
	else
		return (divide_str_meta(string, string->next));
}

t_word_list	*find_meta(t_word_list *string)
{
	t_word_list	*tmp;

	tmp = string;
	string = argument_flag(string);
	while (string != NULL)
	{
		string = split_argument(string);
		string = string->next;
	}
	string = tmp;
	return (tmp);
}
