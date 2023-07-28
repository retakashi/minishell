/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:11:24 by sraza             #+#    #+#             */
/*   Updated: 2023/07/28 20:51:35 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"execve_cmd.h"
#include"libft/libft.h"
// t_word_list	*first_list_quotes(t_word_list	*string)
// {
// 	char	**split;
// 	char	flag;
// 	size_t	i;
// 	t_word_list	*new;

// 	i = 0;
// 	while (string->word[i] != '\0' &&
// 		(string->word[i] == '"' || string->word[i] == '\''))
// 		i++;
// 	if (string->word[i] != '\0' && i != ft_strlen(string->word))
// 	{
// 		flag = string->word[i];
// 		split = ft_split(string->word, flag);
// 	}
// 	else 
// 		return (string);
// 	new = ft_newlst(split[0]);
// 	new->next = string;
// 	free(string->word);
// 	string->word = ft_strdup(split[1]);
// 	return (new);
// }

t_word_list	*make_first_list(char **line)
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
	// string = first_list_quotes(string);
	*line += i;
	while (**line == ' ' || **line == '\t')
		(*line)++;
	return (string);
}

t_word_list	*make_last_list(char **line, t_word_list *string)
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
