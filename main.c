/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:02:28 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/28 20:07:59 by razasharuku      ###   ########.fr       */
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
	t_env_list	*env_list;

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
			line = change_line(line, env_list);
			printf("%s \n", line);
			// parse_line(line);
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
