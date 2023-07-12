/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:11:24 by sraza             #+#    #+#             */
/*   Updated: 2023/07/12 15:13:28 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/*新しいリストを作る→次のノードの指す場所はNUll埋めする*/
t_word_list	*ft_newlst(char *content)
{
	t_word_list	*new;

	new = malloc(sizeof(t_word_list));
	if (new == NULL)
		return (NULL);
	new->word = ft_strdup(content);
	new->next = NULL;
	return (new);
}

int	dquotes_sprt(char *line, int i)
{
	while (*line != ' ')
		line++;
	while (*line != '"')
	{
		i++;
		line++;
	}
	i++;
	return (i);
}

int	squotes_sprt(char *line, int i)
{
	while (*line != ' ')
		line++;
	while (*line != '\'')
	{
		i++;
		line++;
	}
	i++;
	return (i);
}

t_word_list *creat_list(char *line, int i)
{
	char 		*content;
	t_word_list	*new;

	if (*line == '"')
		i = dquotes_sprt(line, i);
	if (*line == '\'')
		i = squotes_sprt(line, i);
	content = malloc(sizeof (char) * (i + 1));
	content = duplicate(content, line, i);
	new = ft_newlst(content);
	free(content);
	return (new);
}

t_word_list *sp_sprt(char **line, t_word_list *string, int i)
{
	t_word_list	*new;

	// printf("before list :i = %i,  line = %s\n", i, *line);
	new = creat_list(*line, i);
	string->next = new;
	string = string->next;
	*line += (ft_strlen(new->word));
	// printf("After list :line = %s, new->word = %zu\n", *line, ft_strlen(new->word));
	return (string);
}

t_word_list *copy_make_list(char *line)
{
	int			i;
	t_word_list	*string;
	t_word_list	*tmp;

	i = 0;
	while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
		i++;
	string = creat_list(line, i);
	line += i;
	while (*line == ' ' || *line == '\t')
		line++;
	tmp = string;
	i = 0;
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
	return (tmp);
}
