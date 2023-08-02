/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 11:58:41 by sraza             #+#    #+#             */
/*   Updated: 2023/08/02 14:26:52 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	is_just_meta(char *str)
{
	t_flags	meta_num;

	meta_num = 0;
	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
		meta_num = pipe_char;
	else if (ft_strncmp(str, ">", 1) == 0)
	{
		if (ft_strlen(str) == 2)
			if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
				meta_num = append;
		if (ft_strlen(str) == 1)
			if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
				meta_num = output;
	}
	else if (ft_strncmp(str, "<", 1) == 0)
	{
		if (ft_strlen(str) == 2)
			if (ft_strncmp(str, "<<", ft_strlen(str)) == 0)
				meta_num = heredoc;
		if (ft_strlen(str) == 1)
			if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
				meta_num = input;
	}
	return (meta_num);
}

int	is_include_meta(char *str)
{
	t_flags	meta_num;

	meta_num = 0;
	if (ft_strncmp(str, "|", 1) == 0)
		meta_num = pipe_char;
	else if (ft_strncmp(str, ">", 1) == 0)
	{
		if (ft_strncmp(str, ">>", 2) == 0)
			meta_num = append;
		else if (ft_strncmp(str, ">", 1) == 0)
			meta_num = output;
	}
	else if (ft_strncmp(str, "<", 1) == 0)
	{
		if (ft_strncmp(str, "<<", 2) == 0)
			meta_num = heredoc;
		else if (ft_strncmp(str, "<", 1) == 0)
			meta_num = input;
	}
	return (meta_num);
}

char	*give_flag(int i)
{
	char	*char_flag;

	if (i == pipe_char)
		char_flag = "|";
	if (i == append)
		char_flag = ">>";
	if (i == output)
		char_flag = ">";
	if (i == heredoc)
		char_flag = "<<";
	if (i == input)
		char_flag = "<";
	return (char_flag);
}

t_word_list	*divide_meta_str(t_word_list *string, int flag)
{
	t_word_list	*tmp2;
	t_word_list	*new;
	char		*char_flag;

	char_flag = give_flag(flag);
	tmp2 = string->next;
	string->word = (string->word + ft_strlen(char_flag));
	new = ft_newlst(string->word);
	// free(string->word);
	string->word = malloc(sizeof (char) * (ft_strlen(char_flag) + 1));
	if (string->word == NULL)
		return (NULL);
	string->word = duplicate(string->word, char_flag, ft_strlen(char_flag));
	string->next = new;
	new->next = tmp2;
	return (string);
}

int	is_just_str(t_word_list *string)
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
	// while (ft_isalnum(string->word[i]) && string->word[i] != '\0')
	while ((ft_isalnum(string->word[i]) || (is_include_meta(&string->word[i])) == 0) && string->word[i] != '\0')
		i++;
	if (string->word[i] == '\0')
		return (1);
	else
		return (0);
}

int	len_of_str_meta(char *str)
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

t_word_list	*divide_str_meta(t_word_list *string, t_word_list *tmp2)
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

t_word_list	*split_argument(t_word_list *string)
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
		printf( "\nstring->word = %s\n", string->word);
		string = string->next;
	}
	return (tmp);
}
