/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:11:24 by sraza             #+#    #+#             */
/*   Updated: 2023/08/17 10:45:04 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	t_word_list	*make_first_list(char **line)
{
	int			i;
	t_word_list	*string;
	char		quote;

	i = 0;
	while (**line == ' ' || **line == '\t')
		(*line)++;
	while ((*line)[i] != ' ' && (*line)[i] != '\t' && (*line)[i] != '\0')
	{
		if ((*line)[i] == '"' || (*line)[i] == '\'')
		{
			quote = (*line)[i];
			i++;
			while ((*line)[i] != quote && (*line)[i] != '\0')
				i++;
		}
		i++;
	}
	string = creat_list(*line, i);
	*line += i;
	while (**line == ' ' || **line == '\t')
		(*line)++;
	return (string);
}

static	t_word_list	*connect_process(t_word_list *tmp, t_word_list *tmp2)
{
	char		*str;
	t_word_list	*tmp3;

	while (tmp->next != NULL)
	{
		tmp3 = tmp->next->next;
		str = ft_strdup(tmp->word);
		free(tmp->word);
		tmp->word = ft_strjoin(str, tmp->next->word);
		free(tmp->next->word);
		free(tmp->next);
		free(str);
		tmp->next = tmp3;
	}
	return (tmp2);
}

static	t_word_list	*connect_words(t_word_list *tmp)
{
	int			len;
	t_word_list	*tmp2;

	tmp2 = tmp;
	len = len_of_string(tmp);
	if (len > 1)
	{
		tmp = argument_flag(tmp);
		tmp = trim_quotes(tmp);
		tmp = connect_process(tmp, tmp2);
		print_words(tmp);
	}
	return (tmp2);
}

static	t_word_list	*make_last_list(char **line, t_word_list *string)
{
	int			i;
	t_word_list	*new;
	t_word_list	*tmp;
	int			count;

	i = 0;
	count = 0;
	tmp = NULL;
	while ((*line)[i] != ' ' && (*line)[i] != '\t' && (*line)[i] != '\0')
		i++;
	if (i != 0)
	{
		while (**line != '\0')
		{
			new = creat_list(*line, i);
			string->next = new;
			string = string->next;
			(*line) += (ft_strlen(new->word));
			if (count == 0)
				tmp = new;
			count++;
		}
	}
	string = connect_words(tmp);
	return (string);
}

t_word_list	*make_list(char *line)
{
	int			i;
	t_word_list	*string;
	t_word_list	*tmp;

	i = 0;
	string = make_first_list(&line);
	tmp = string;
	while (string->next != NULL)
		string = string->next;
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
	string = make_last_list(&line, string);
	string = tmp;
	string = find_meta(string);
	return (string);
}
