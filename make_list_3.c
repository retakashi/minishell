/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 11:58:41 by sraza             #+#    #+#             */
/*   Updated: 2023/07/23 13:34:00 by sraza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	is_meta(char *str)
{
	t_flags	meta_num;

	meta_num = 0;
	if (ft_strnstr(str, "|", ft_strlen(str)))
		meta_num = pipe_char;
	else if (ft_strnstr(str, ">>", ft_strlen(str)))
		meta_num = append;
	else if (ft_strnstr(str, ">", ft_strlen(str)))
		meta_num = output;
	else if (ft_strnstr(str, "<<", ft_strlen(str)))
		meta_num = heredoc;
	else if (ft_strnstr(str, "<", ft_strlen(str)))
		meta_num = input;
	return (meta_num);
}

t_word_list	*split_list(t_word_list *string, char *flag)
{
	t_word_list	*tmp;
	t_word_list	*tmp2;
	t_word_list	*new;
	char		**split;
	int			i;

	i = 1;
	tmp = string;
	if (string->flag == 3)
		return (string->next);
	split = split_str(string->word, flag);
	if (split == NULL)
		return (tmp);
	tmp2 = string->next;
	if (string != NULL && string->word[0] == flag[0])	
	{
		string->word = ft_strdup(flag);
		new = ft_newlst(split[0]);
		string->next = new;
		string = string->next;
		string->next = tmp2;
		return (tmp);
	}
	string->word = ft_strdup(split[0]);
	new = ft_newlst(flag);
	string->next = new;
	string = string->next;
	while (split[i])
	{
		new = creat_list(split[i], ft_strlen(split[i]));
		string->next = new;
		string = string->next;
		if (split[i + 1] != NULL)
		{
			new = ft_newlst(flag);
			string->next = new;
			string = string->next;
		}
		i++;
	}
	string->next = tmp2;
	ft_free_line2(split);
	return (tmp);
}

t_word_list	*find_meta(t_word_list *string)
{
	t_word_list	*tmp;
	t_flags 	flag;

	tmp = string;
	string = argument_flag(string);
	while (string != NULL)
	{
		flag = is_meta(string->word);
		if (flag == 5 && (ft_strlen(string->word) > 1))
			string = split_list(string, "|");
		if (flag == 6 && (ft_strlen(string->word) > 1))
			string = split_list(string, ">");
		if (flag == 7 && (ft_strlen(string->word) > 2))
			string = split_list(string, ">>");
		if (flag == 8 && (ft_strlen(string->word) > 1))
			string = split_list(string, "<");
		if (flag == 9 && (ft_strlen(string->word) > 2))
			string = split_list(string, "<<");
		if (flag == 0 || (ft_strlen(string->word) <= 2))
			string = string->next;
	}
	return (tmp);
}
