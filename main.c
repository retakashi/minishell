/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:02:28 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/13 16:30:31 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
//meta_char | & ; ( ) space tab  < > == less,great,| == pipe_char

void	free_g_list(void)
{
	t_envp	*next;

	if (g_envp_list == NULL)
		return ;
	if (g_envp_list->word_head != NULL)
		// free_word_list(); まだ
		while (g_envp_list != NULL)
		{
			next = g_envp_list->next;
			free(g_envp_list->envp_name);
			free(g_envp_list->envp_str);
			free(g_envp_list);
			g_envp_list = next;
		}
	g_envp_list = NULL;
}

void	check_syntax_error(t_word_list *head)
{
	if (head != NULL && head->flag == pipe_char)
		perror_free_2d_arr_exit("|", NULL, NULL, SYNTAX_ERROR);
	if (head != NULL && (ft_strcmp(head->word, "&") == 0
			|| ft_strchr(head->word, ";") == 0))
		perror_free_2d_arr_exit(head->word, NULL, NULL, SYNTAX_ERROR);
}

void	read_word_list(t_word_list *head)
{
	while (head != NULL)
	{
		check_syntax_error(head);
		if (head != NULL && (head->flag == great || head->flag == less))
			main_redirection(&head);
		else if (head != NULL && (head->flag == great_great
					|| head->flag == less_less))
			main_heredoc_or_additionally_write(&head);
		else if (head != NULL && head->flag == arguments && is_builtin(head))
			main_builtin(&head);
		else if (head != NULL && head->flag == arguments && !is_builtin(head))
			main_command(&head);
	}
}

void	is_command(t_word_list **head)
{
	if ((*head)->flag == arguments)
		(*head)->flag = command;
	while (*head != NULL)
	{
		*head = (*head)->next;
		while (*head != NULL && (*head)->flag != pipe_char)
			*head = (*head)->next;
		if (*head == NULL || (*head)->next == NULL)
			break ;
		if ((*head)->flag == pipe_char)
		{
			*head = (*head)->next;
			(*head)->flag == command;
		}
	}
	*head = g_envp_list->word_head;
}

void	minishell_init(char **envp)
{
	t_word_list	*word_head;

	g_envp_list = NULL;
	if (envp != NULL)
		get_envp_list(envp);
	// get_word_list(&word_head); まだ
	g_envp_list->word_head = word_head;
	is_command(&word_head);
	read_word_list(word_head);
	free_g_list();
	//free_word_list(head);
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
