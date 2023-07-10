/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:39:25 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/08 17:31:02 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include"./libft/libft.h"
#include"minishell.h"


t_word_list	*ft_newlst(void *content)
{
	t_word_list	*new;

	new = malloc(sizeof(t_word_list));
	if (new == NULL)
		return (NULL);
	new->word = content;
	new->next = NULL;
	return (new);
}

t_word_list *make_list(char **list)
{
	int			i;
	t_word_list	*string;
	t_word_list	*new;
	t_word_list	*tmp;

	i = 1;
	string = ft_newlst(list[0]);
    printf("%s \n", string->word);
	tmp = string;
	while (list[i] != NULL)
	{
		new = ft_newlst(list[i]);
		new->flag = i;
		string->next = new;
		string = new;
		i++;
	}
	printf("--------------\n");
    i = 0;
    string = tmp;
	while (list[i])
	{
		printf("%s \n", string->word);
		printf("%i \n", string->flag);
		string = string->next;
		i++;
	}
    string = tmp;
	return (string);
}

void	*ft_free_line2(char **result)
{
	size_t	i;

	i = 0;
	while (result[i] != NULL)
	{
		free(result[i]);
		result[i] = NULL;
		i++;
	}
	free(result);
	result = NULL;
	return (NULL);
}



void	parse_line(const char *line)
{
	char	    **line2;
    t_word_list	*string;
    int i;

	if (*line == '#' || line[strlen(line) - 1] == '|')
	{
		printf(" comment out or End with pipe!\n");
		return ;
	}
	line2 = ft_split(line, ' ');
    i = 0;
    while (line2[i])
	{
		printf("%s \n", line2[i]);
		i++;
	}
    printf("####################################\n");
    string = make_list(line2);
    ft_free_line2(line2);
	while (string->word != NULL)
	{
		printf("string->word = %s \n", string->word);
        string = string->next;
	}
	return ;
}