/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:02:28 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/23 03:29:11 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
//meta_char | & ; ( ) space tab  < > == input,output,| == pipe_char

void	read_word_list(t_word_list *word_list, t_env_list **env_list,
		t_fd **fd_struct)
{
	// if (is_word_list_flags(word_list, pipe_char) == true)
	// 	do_pipe();
	// else
	// {
	if (is_word_list_flags(word_list, heredoc) == true)
		main_heredoc(word_list, *fd_struct);
	if (is_word_list_flags(word_list, output) == true)
		input_output_operation(word_list, fd_struct, output);
	if (is_word_list_flags(word_list, input) == true
		&& input_output_operation(word_list, fd_struct, input) == FAILURE)
		return ;
	if (is_word_list_flags(word_list, append) == true
		&& input_output_operation(word_list, fd_struct, append) == FAILURE)
		return ;
	main_command(&word_list, env_list);
	// }
}

void	init_minishell(char **envp,
					t_env_list **env_list_head,
					t_word_list **word_list_head,
					t_fd **fd_list_head)
{
	*word_list_head = NULL;
	*fd_list_head = NULL;
	*env_list_head = NULL;
	if (envp != NULL)
		get_env_list(envp, env_list_head);
}

void	restore_stdfd(t_fd **fd_list)
{
	while (*fd_list != NULL && (*fd_list)->next != NULL)
		*fd_list = (*fd_list)->next;
	if ((*fd_list)->fd_flg == SAVE_STDOUT)
	{
		while (*fd_list!=NULL&&(*fd_list)->fd_flg == SAVE_STDOUT)
		{
			dup2((*fd_list)->fd, STDOUT_FILENO);
			*fd_list = (*fd_list)->prev;
		}
	}
	else
	{
		while (*fd_list!=NULL&&(*fd_list)->fd_flg == SAVE_STDIN)
		{
			dup2((*fd_list)->fd, STDIN_FILENO);
			*fd_list = (*fd_list)->prev;
		}
	}
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }

int	main(int argc, char **argv, char **envp)
{
	t_word_list	*word_head;
	t_env_list	*env_list_head;
	t_fd		*fd_list_head;
	char		*line;

	if (argc == 0 || argv == NULL)
		return (0);
	init_minishell(envp, &env_list_head, &word_head, &fd_list_head);
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
		read_word_list(word_head, &env_list_head, &fd_list_head);
	}
	restore_stdfd(&fd_list_head);
	free(line);
	free_word_list(&word_head);
	}
	free_env_list(&env_list_head);
	return (0);
}
