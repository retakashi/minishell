/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:58:42 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/12 18:04:25 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_word_list	*argument_flag(t_word_list *string)
{
	t_word_list	*tmp;

	tmp = string;
	while (tmp != NULL)
	{
		tmp->flag = 0;
		tmp = tmp->next;
	}
	tmp = string;
	while (tmp != NULL)
	{
		if (tmp->word != NULL && (tmp->word[0] == '"' || tmp->word[0] == '\''))
			tmp->flag = 3;
		tmp = tmp->next;
	}
	tmp = string;
	return (string);
}

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
	char		*content;

	char_flag = give_flag(flag);
	tmp2 = string->next;
	content = &(string->word[ft_strlen(char_flag)]);
	new = ft_newlst(content);
	free(string->word);
	string->word = malloc(sizeof (char) * (ft_strlen(char_flag) + 1));
	if (string->word == NULL)
		return (NULL);
	string->word = duplicate(string->word, char_flag, ft_strlen(char_flag));
	string->next = new;
	new->next = tmp2;
	return (string);
}
