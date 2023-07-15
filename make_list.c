/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:11:24 by sraza             #+#    #+#             */
/*   Updated: 2023/07/15 15:40:35 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


int	is_meta(char *str)
{
	t_flags	meta_num;

	meta_num = 0;
	if (ft_strrchr(str, '|'))
		meta_num = pipe_char;
	if (ft_strncmp(str, ">", ft_strlen(str)))
		meta_num = great;
	// if (ft_strncmp(str, ">>", ft_strlen(str)))
	// 	meta_num = great_great;
	if (ft_strncmp(str, "<", ft_strlen(str)))
		meta_num = less;
	// if (ft_strncmp(str, "<<", ft_strlen(str)))
	// 	meta_num = less_less;
	return (meta_num);
}

t_word_list	*split_list(t_word_list *string, char *flag)
{
	t_word_list *tmp;
	t_word_list *new;

	char 		**split;
	int			i;

	i = 1;
	tmp = string;
	split = split_str(string->word, flag);
	if (split == NULL)
		return (tmp);
	string->word = ft_strdup(split[0]);
	new = ft_newlst(flag);
	string->next = new;
	string = string->next;
	while (split[i])
	{
		new = creat_list(split[i], ft_strlen(split[i]));
		string->next = new;
		string = string->next;
		new = ft_newlst(flag);
		string->next = new;
		string = string->next;
		i++;
	}
	printf("%s come here!! \n", flag);
	return (tmp);
}

t_word_list	*find_meta(t_word_list *string)
{
	t_word_list	*tmp;
	t_flags flag;

	tmp = string;
	while (string != NULL)
	{
		flag = is_meta(string->word);
		if (flag == 5 && (ft_strlen(string->word) > 1))
			string = split_list(string, "|");
		else if (flag == 6 && (ft_strlen(string->word) > 1))
			string = split_list(string, ">");
		else if (flag == 7 && (ft_strlen(string->word) > 2))
			string = split_list(string, ">>");
		else if (flag == 8 && (ft_strlen(string->word) > 1))
			string = split_list(string, "<");
		string = string->next;
	}
	return (tmp);
}


t_word_list	*make_list(char *line)
{
	int			i;
	t_word_list	*string;
	t_word_list	*tmp;

	i = 0;
	//make first_list
	while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
		i++;
	string = creat_list(line, i);
	line += i;
	while (*line == ' ' || *line == '\t')
		line++;
	tmp = string;
	i = 0;
	//make intermediate_list
	while (*line != '\0' && line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '\t')
		{
			string = sp_sprt(&line, string, i);
			while (*line == ' ' || *line == '\t')
				line++;
			i = -1;
		}
		i++;
	}
	//make last_list
	while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
		i++;
	if (i != 0)
	{
		string->next = creat_list(line, i);
		string->next->next = NULL;
	}
	string = tmp;
	string = find_meta(string);
	return (tmp);
}
