/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:11:24 by sraza             #+#    #+#             */
/*   Updated: 2023/08/09 17:38:54 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	t_word_list	*make_first_list(char **line)
{
	int			i;
	t_word_list	*string;

	i = 0;
	while (**line == ' ' || **line == '\t')
		(*line)++;
	while ((*line)[i] != ' ' && (*line)[i] != '\t' && (*line)[i] != '\0')
	{
		if ((*line)[i] == '"' || (*line)[i] == '\'')
		{
			i++;
			while ((*line)[i] != '"' && (*line)[i] != '\''
				&& (*line)[i] != '\0')
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

static	t_word_list	*make_last_list(char **line, t_word_list *string)
{
	int	i;

	i = 0;
	while ((*line)[i] != ' ' && (*line)[i] != '\t' && (*line)[i] != '\0')
		i++;
	if (i != 0)
	{
		string->next = creat_list(*line, i);
		string->next->next = NULL;
	}
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