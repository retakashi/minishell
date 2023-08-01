/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_3_12.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 11:58:41 by sraza             #+#    #+#             */
/*   Updated: 2023/08/01 16:17:26 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	is_just_meta(char *str)
{
	t_flags	meta_num;

	meta_num = 0;
	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
		meta_num = pipe_char;
	else if (*str == ">")
	{
		if (ft_strlen(str) == 1)
			if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
				meta_num = output;
		if (ft_strlen(str) == 2)
			if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
				meta_num = append;
	}
	else if (*str == "<")
	{
		if (ft_strlen(str) == 1)
			if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
				meta_num = input;
		if (ft_strlen(str) == 2)
			if (ft_strncmp(str, "<<", ft_strlen(str)) == 0)
				meta_num = heredoc;
	}
	return (meta_num);
}

// int	is_just_meta(char *str)
// {
// 	t_flags	meta_num;

// 	meta_num = 0;
// 	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
// 		meta_num = pipe_char;
// 	else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
// 		meta_num = append;
// 	else if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
// 		meta_num = output;
// 	else if (ft_strncmp(str, "<<", ft_strlen(str)) == 0)
// 		meta_num = heredoc;
// 	else if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
// 		meta_num = input;
// 	return (meta_num);
// }

int	is_include_meta(char *str)
{
	t_flags	meta_num;

	meta_num = 0;
	if (ft_strncmp(str, "|", 1) == 0)
		meta_num = pipe_char;
	else if (*str == ">")
	{
		if (ft_strncmp(str, ">>", 2) == 0)
			meta_num = append;
		if (ft_strncmp(str, ">", 1) == 0)
			meta_num = output;
	}
	else if (*str == "<")
	{
		if (ft_strncmp(str, "<<", 2) == 0)
			meta_num = heredoc;
		if (ft_strncmp(str, "<", 1) == 0)
			meta_num = input;
	}
	// else if (ft_strncmp(str, ">>", 2) == 0)
	// 	meta_num = append;
	// else if (ft_strncmp(str, ">", 1) == 0)
	// 	meta_num = output;
	// else if (ft_strncmp(str, "<<", 2) == 0)
	// 	meta_num = heredoc;
	// else if (ft_strncmp(str, "<", 1) == 0)
	// 	meta_num = input;
	return (meta_num);
}


t_word_list	*divide_meta_str(t_word_list *string, int flag)
{
	char		*char_flag;
	t_word_list	*tmp;
	t_word_list	*tmp2;
	t_word_list	*new;
	char		*str;

	tmp = string;
	tmp2 = string->next;
	if (flag == 5)
		char_flag = "|";
	if (flag == 7)
		char_flag = ">>";
	if (flag == 6)
		char_flag = ">";
	if (flag == 9)
		char_flag = "<<";
	if (flag == 8)
		char_flag = "<";
	str = char_flag;

}

int	is_just_str(t_word_list *string)
{
	if (*string->word == '"')
	{
		string->word++;
		while (*string->word != '"' && *string->word != '\0')
			string->word++;
		if (*string->word == '"' && *(string->word + 1) != '\0')
			return (1);
	}
	if (*string->word == '\'')
	{
		string->word++;
		while (*string->word != '\'' && *string->word != '\0')
			string->word++;
		if (*string->word == '\'' && *(string->word + 1) != '\0')
			return (1);
	}
	while (ft_isalnum(*string->word) && *string->word != '\0')
		string->word++;
	if (*string->word == '\0')
		return (1);
	else
		return (0);
}

t_word_list	*split_argument(t_word_list *string)
{
	
	if (is_just_meta(string->word) != 0)
		return (string);
	if (is_just_str(string) != 0)
		return (string);
	if (is_include_meta(string->word) != 0)
		return (string);

}

t_word_list	*find_meta(t_word_list *string)
{
	t_word_list	*tmp;
	// t_flags 	flag;

	tmp = string;
	string = argument_flag(string);
	while (string != NULL)
	{
		string = split_argument(string);
		string = string->next;
		// flag = is_meta(string->word);
		// printf("flag : %d\n", flag);
		// if (flag == 5 && (ft_strlen(string->word) > 1))
		// 	string = split_list(string, "|");
		// if (flag == 7 && (ft_strlen(string->word) > 2))
		// 	string = split_list(string, ">>");
		// if (flag == 6 && (ft_strlen(string->word) > 1))
		// 	string = split_list(string, ">");
		// if (flag == 9 && (ft_strlen(string->word) > 2))
		// 	string = split_list(string, "<<");
		// if (flag == 8 && (ft_strlen(string->word) > 1))
		// 	string = split_list(string, "<");
		// if (flag == 0 || (ft_strlen(string->word) <= 2))
			// string = string->next;
	}
	return (tmp);
}
