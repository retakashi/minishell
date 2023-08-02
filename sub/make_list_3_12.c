/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 11:58:41 by sraza             #+#    #+#             */
/*   Updated: 2023/07/31 23:25:22 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	is_just_meta(char *str)
{
	t_flags	meta_num;

	meta_num = 0;
	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
		meta_num = pipe_char;
	else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		meta_num = append;
	else if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		meta_num = output;
	else if (ft_strncmp(str, "<<", ft_strlen(str)) == 0)
		meta_num = heredoc;
	else if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		meta_num = input;
	return (meta_num);
}

int	is_include_meta(char *str)
{
	t_flags	meta_num;

	meta_num = 0;
	if (ft_strncmp(str, "|", 1) == 0)
		meta_num = pipe_char;
	else if (ft_strncmp(str, ">>", 2) == 0)
		meta_num = append;
	else if (ft_strncmp(str, ">", 1) == 0)
		meta_num = output;
	else if (ft_strncmp(str, "<<", 2) == 0)
		meta_num = heredoc;
	else if (ft_strncmp(str, "<", 1) == 0)
		meta_num = input;
	return (meta_num);
}

// t_word_list	*append_meta(t_word_list *string, int flag)
// {
	
// }

t_word_list	*split_argument(t_word_list *string)
{
	char *str;
	int i;
	t_word_list *tmp;
	t_word_list *new;
	t_word_list *tmp2;

	tmp = string;
	tmp2 = string->next;
	i = 0;
	str = string->word;
	if (is_just_meta(str) != 0)
		return (string);
	while (*str)
	{
		while (ft_isalnum(*str))
			i++;
		if (*str == '\0')
			return (string);
		else
		{
			free(string->word);
			string->word = malloc(sizeof (char) * (i + 1));
			string->word = duplicate(string->word, str, i);
			while (i-- > 0)
				str++;
			new = ft_newlst(str);
			string->next = new;
			string = string->next;
		}
		// if (is_include_meta(str) != 0)
		// 	string = append_meta(string, is_include_meta(str));
	}
	string->next = tmp2;
	return (tmp);
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
