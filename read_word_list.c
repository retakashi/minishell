/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_word_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:02:28 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/28 00:52:21 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

bool	is_word_list_flag(t_word_list *word_list, int flag)
{
	while (word_list != NULL)
	{
		if (word_list->flag == flag)
			return (true);
		word_list = word_list->next;
	}
	return (false);
}

int	pipe_cnt(t_word_list *word_list)
{
	int	cnt;

	cnt = 0;
	while (word_list != NULL)
	{
		if (word_list->flag == pipe_char && word_list->next != NULL)
			cnt++;
		word_list = word_list->next;
	}
	return (cnt);
}

void	get_here_list_child_num(t_word_list *word_list, t_here_list **here_list)
{
	int	flg;
	int	i;

	i = 0;
	while (word_list != NULL)
	{
		flg = false;
		while (word_list != NULL && word_list->flag != pipe_char)
		{
			if (flg == false && word_list->flag == heredoc)
			{
				(*here_list)->child_num = i;
				flg = true;
			}
			word_list = word_list->next;
		}
		i++;
		if (word_list != NULL)
			word_list = word_list->next;
	}
}

int	read_word_list(t_word_list *word_list, t_env_list **env_list,
		t_here_list **here_list)
{
	int	cnt;
	int	builtin_flg;

	if (is_word_list_flag(word_list, eof_num) == true
		&& get_heredoc_list(word_list, here_list, env_list) == FAILURE)
		return (FAILURE);
	cnt = pipe_cnt(word_list);
	if (cnt == 0 && is_builtin(word_list, &builtin_flg) == true
		&& execve_builtin(word_list, env_list, *here_list,
			builtin_flg) == FAILURE)
		return (FAILURE);
	else
	{
		if (here_list != NULL)
			get_here_list_child_num(word_list, here_list);
		if (fork_execve_cmd(word_list, env_list, *here_list, cnt) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

void	init_minishell(char **envp, t_env_list **env_list_head,
		t_word_list **word_list_head, t_here_list **here_list)
{
	*word_list_head = NULL;
	*env_list_head = NULL;
	*here_list = NULL;
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
	t_here_list	*here_list_head;
	char		*line;

	if (argc == 0 || argv == NULL)
		return (0);
	init_minishell(envp, &env_list_head, &word_head, &here_list_head);
	while (1)
	{
		line = readline("minishell$ ");
		// line = "cat | ls";
		if (line == NULL)
			break ;
		if (*line)
		{
			// parse_line(line);
			// add_history(line);
			get_word_list(&word_head, line);
			get_command(&word_head);
			read_word_list(word_head, &env_list_head, &here_list_head);
		}
		free(line);
		free_word_list(&word_head);
		free_here_list(&here_list_head);
	}
	free_env_list(&env_list_head);
	return (0);
}
