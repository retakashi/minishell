/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:39:25 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/11 14:53:20 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_word_list *creat_list(char *line, int i)
{
	char 		*content;
	t_word_list	*new;

	content = malloc(sizeof (char) * (i + 1));
	content = duplicate(content, line, i);
	new = ft_newlst(content);
	free(content);
	return (new);
}


t_word_list *copy_make_list(char *line)
{
	int	i;
	int i_wait;
	t_word_list	*string;
	t_word_list	*new;
	t_word_list	*tmp;


	i = 0;
	i_wait = 0;
	string = ft_newlst(&line[0]);
	string->word = "raza";
	tmp = string;
	while (*line != '\0')
	{
		if (line[i] == ' ' || line[i] == '\t')
		{
			printf("before list :i = %i, i_wait = %i  line = %s\n", i, i_wait, line);
			new = creat_list(line, i - i_wait);
			string->next = new;
			string = string->next;
			line += (i - i_wait + 1);
			printf("after list : line = %s\n", line);
			i_wait = 0;
			i = 0;
		}
		i++;
	}
	printf("End of creating list\n");
	return (tmp);
}


void	parse_line(char *line)
{
	// char		**line2;
	t_word_list	*string;
	t_word_list	*tmp;
	// char		*line_ptr;

	if (*line == '#' || line[strlen(line) - 1] == '|')
	{
		printf(" comment out or End with pipe!\n");
		return ;
	}
	// line2 = ft_split(line, ' ');
	// line_ptr = line;
	string = copy_make_list(line);
	tmp = string;
	// ft_free_line2(line2);
	while (string != NULL)
	{
		printf("string->word = %s \n", string->word);
		string = string->next;
	}
	string = tmp;
	return ;
}

