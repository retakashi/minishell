/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:02:28 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/23 21:05:56 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
//meta_char | & ; ( ) space tab  < > == input,output,| == pipe_char

bool	is_word_list_flags(t_word_list **word_list, int flags)
{
	while (*word_list != NULL || (*word_list)->flag != pipe_char)
	{
		if ((*word_list)->flag == flags)
			return (true);
		*word_list = (*word_list)->next;
	}
	return (false);
}

void	read_word_list(t_word_list *word_list, t_env_list **env_list,
		t_fd *fd_struct)
{
	t_word_list	*word_head;

	// if (is_word_list_flags(word_list, pipe_char) == true)
	// 	do_pipe();
	// else
	// {
	if (is_word_list_flags(&word_list, heredoc_file) == true)
		main_heredoc(word_list, &fd_struct);
	word_list = word_head;
	if (is_word_list_flags(word_list, output) == true)
		input_output_operation(word_list, &fd_struct, output);
	if (is_word_list_flags(word_list, input) == true
		&& input_output_operation(word_list, &fd_struct, input) == FAILURE)
		return ;
	if (is_word_list_flags(word_list, append) == true
		&& input_output_operation(word_list, &fd_struct, append) == FAILURE)
		return ;
	main_command(&word_list, env_list, fd_struct);
	// }
}

void	init_minishell(char **envp,
					t_env_list **env_list_head,
					t_word_list **word_list_head,
					t_fd *fd_struct)
{
	*word_list_head = NULL;
	*env_list_head = NULL;
	fd_struct->is_append = false;
	fd_struct->is_heredoc = false;
	fd_struct->in_fd = STDIN_FILENO;
	fd_struct->out_fd = STDOUT_FILENO;
	if (envp != NULL)
		get_env_list(envp, env_list_head);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }

int	main(int argc, char **argv, char **envp)
{
	t_word_list	*word_head;
	t_env_list	*env_list_head;
	t_fd		*fd_struct;
	char		*line;

	if (argc == 0 || argv == NULL)
		return (0);
	init_minishell(envp, &env_list_head, &word_head, &fd_struct);
	while (1)
	{
		line = readline("minishell$ ");
		// line = "echo hello  > file1 > file2";
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
		free_word_list(&word_head);
	}
	free_env_list(&env_list_head);
	return (0);
}
