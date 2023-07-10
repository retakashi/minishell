/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:02:43 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/08 15:33:39 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
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

int	main(int argc, char **argv)
{
	// char		**list;
	int			i;
	t_word_list	*string;
	t_word_list	*new;
	t_word_list	*tmp;

	i = 1;
	if (argc == 1)
		return (0);

	string = ft_newlst(argv[0]);
	tmp = string;
	while (argv[i] != NULL)
	{
		new = ft_newlst(argv[i]);
		new->flag = i;
		string->next = new;
		string = new;
		printf("--------------\n");
		i++;
	}
	string = tmp;
	i = 0;
	while (argv[i])
	{
		printf("%s \n", string->word);
		printf("%i \n", string->flag);
		string = string->next;
		i++;
	}
	return (0);
}