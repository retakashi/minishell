/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:02:28 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/21 23:02:40 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
//meta_char | & ; ( ) space tab  < > == less,great,| == pipe_char

bool	is_word_list_flags(t_word_list *word_list, int flags)
{
	while (word_list != NULL)
	{
		if (word_list->flag == flags)
			return (true);
		word_list = word_list->next;
	}
	return (false);
}

void	read_word_list(t_word_list *word_list, t_env_list **env_list,
		t_fd *fd_struct)
{
	// if (is_word_list_flags(word_list, pipe_char) == true)
	// 	do_pipe();
	// else
	// {
		if (is_word_list_flags(word_list, less_less) == true)
			create_heredoc(word_list, fd_struct);
		if (is_word_list_flags(word_list, great) == true)
			main_redirection(word_list, fd_struct, great);
		if (is_word_list_flags(word_list, less) == true)
			main_redirection(word_list, fd_struct, less);
		if (is_word_list_flags(word_list, great_great) == true)
			additionally_write(word_list, fd_struct);
	main_command(&word_list, env_list);
	// }
}

void	init_fd_struct(t_fd *fd_struct)
{
	fd_struct->here_fd = 0;
	fd_struct->in_fd = 0;
	fd_struct->out_fd = 0;
	fd_struct->pipe_fd[0] = 0;
	fd_struct->pipe_fd[1] = 0;
}

void	init_minishell(char **envp,
					t_env_list **env_list_head,
					t_fd *fd_struct)
{
	if (envp != NULL)
		get_env_list(envp, env_list_head);
	init_fd_struct(fd_struct);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }

int	main(int argc, char **argv, char **envp)
{
	t_word_list	*word_head;
	t_env_list	*env_list_head;
	t_fd		fd_struct;
	char		*line;

	if (argc == 0 || argv == NULL)
		return (0);
	word_head = NULL;
	env_list_head = NULL;
	init_minishell(envp, &env_list_head, &fd_struct);
	while (1)
	{
	line = readline("minishell$ ");
	// line = "echo hello > file";
	if (line == NULL)
		break ;
	if (*line)
	{
		// parse_line(line);
		// add_history(line);
		get_word_list(&word_head, line);
		get_command(&word_head);
		read_word_list(word_head, &env_list_head, &fd_struct);
	}
	free(line);
	}
	return (0);
}
