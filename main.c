/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:02:28 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/15 17:32:47 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
//meta_char | & ; ( ) space tab  < > == less,great,| == pipe_char


void	read_word_list(t_word_list *word_list, t_env_list *env_list,
		t_fd fd_struct)
{
	while (word_list != NULL)
	{
		if (word_list != NULL && word_list->flag == less_less)
			create_heredoc(&word_list, &fd_struct);
		else if (word_list != NULL && (word_list->flag == great
					|| word_list->flag == less))
			main_redirection(&word_list, &fd_struct);
		else if (word_list != NULL && word_list->flag == great_great)
			main_additionally_write(&word_list, &fd_struct);
		else if (word_list != NULL && word_list->flag == command)
			main_command(&word_list);
	}
}

void	init_fd_struct(t_fd *fd_struct)
{
	fd_struct->here_fd = 0;
	fd_struct->in_fd = 0;
	fd_struct->out_fd = 0;
	fd_struct->pipe_fd[0] = 0;
	fd_struct->pipe_fd[1] = 0;
	g_shell_struct->fd_struct = fd_struct;
}

void	init_minishell(char **envp,char **argv)
{
	t_word_list	*word_head;
	t_env_list	*env_list_head;
	t_fd		fd_struct;

	get_word_list(&word_head,argv);
	is_command(&word_head);
	g_shell_struct->word_head = word_head;
	g_shell_struct->env_head = NULL;
	env_list_head = NULL;
	g_shell_struct = envp;
	g_shell_struct->exit_status=0;
	if (envp != NULL)
		get_envp_list(envp, &env_list_head);
	init_fd_struct(&fd_struct);
	read_word_list(word_head, env_list_head, fd_struct);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	if (argc != 0 && argv != NULL)
		return ;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
		{
			// parse_line(line);
			// add_history(line);
			minishell_init(envp,argv);
		}
		free(line);
	}
	return (0);
}
