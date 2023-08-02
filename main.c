/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:02:28 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/01 17:29:01 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(int argc, char **argv, char **env)
{
	char		*line;
	char		*new_line;
	t_env_list	*env_list;

	// t_word_list	*string;
	if (argc > 3)
		return (0);
	if (argv == NULL)
		return (0);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
		{
			env_list = init_minishell(env, &env_list);
			new_line = change_line(line, env_list);
			parse_line(new_line);
			// print_words(string);
			add_history(new_line);
		}
	}
	exit(0);
}

// __attribute__((destructor))
// static void destructor()
// {
// 	system("leaks -q minishell");
// }
