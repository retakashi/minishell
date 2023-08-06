/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:02:28 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/06 18:52:51 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include"minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	char		*new_line;
	t_env_list	*env_list;
	t_word_list	*string;

	if (argc > 3)
		return (0);
	if (argv == NULL)
		return (0);
	
	while (1)
	{
		line = readline("minishell$ ");
		env_list = init_minishell(env, &env_list);
		if (line == NULL)
			break ;
		if (*line)
		{
			new_line = change_line(line, env_list);
			string = parse_line(new_line, env_list);
			free(new_line);
			add_history(line);
		}
	}
	exit(0);
}

// __attribute__((destructor))
// static void destructor()
// {
// 	system("leaks -q minishell");
// }
