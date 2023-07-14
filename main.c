/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:02:28 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/14 23:48:47 by reira            ###   ########.fr       */
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
		else if (word_list != NULL && word_list->flag == command
				&& is_builtin(word_list))
			main_builtin(&word_list, &env_list);
		else if (word_list != NULL && word_list->flag == command
				&& !is_builtin(word_list))
			main_command(&word_list);
	}
}

bool	is_inequality_sign(int flag)
{
	if (flag == great || flag == great || flag == less || flag == less_less)
		return (true);
	return (false);
}

void	is_command(t_word_list **head)
{
	if (*head == NULL)
		return ;
	if ((*head)->flag == arguments)
		(*head)->flag = command;
	else if (is_inequality_sign((*head)->flag == true))
	{
		while ((*head != NULL && (*head)->next != NULL)
			&& (is_inequality_sign((*head)->flag) == true
				&& (*head)->next->flag == arguments))
			*head = (*head)->next->next;
		if (is_inequality_sign((*head)->flag) == true && (*head)->next == NULL)
			perror_exit("newline", SYNTAX_ERROR);
		if (is_inequality_sign((*head)->flag) == true
			&& (*head)->next->flag != arguments)
			perror_exit((*head)->next->word, SYNTAX_ERROR);
		*head = (*head)->next;
		(*head)->flag = command;
	}
}

void	traverse_list_until_pipe(t_word_list **head)
{
	is_command(head);
	while (*head != NULL)
	{
		*head = (*head)->next;
		while (*head != NULL && (*head)->flag != pipe_char)
			*head = (*head)->next;
		if (*head == NULL)
			break ;
		else if ((*head)->flag == pipe_char)
		{
			*head = (*head)->next;
			is_command(head);
		}
	}
	*head = g_shell_struct->word_head;
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

void	init_minishell(char **envp)
{
	t_word_list	*word_head;
	t_env_list	*env_list_head;
	t_fd		fd_struct;

	// get_word_list(&word_head); まだ
	is_command(&word_head);
	g_shell_struct->word_head = word_head;
	g_shell_struct->env_head = NULL;
	env_list_head = NULL;
	g_shell_struct = envp;
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
			minishell_init(envp);
		}
		free(line);
	}
	return (0);
}
