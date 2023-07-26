/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:02:28 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/26 13:20:20 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "execve_cmd.h"

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

int	read_word_list_execve_cmd(t_word_list *word_list, t_env_list **env_list,
		t_fd_list **fd_list)
{
	int	cnt;
	int	builtin_flg;

	if (is_word_list_flag(word_list, eof_num) == true && main_heredoc(word_list,
			fd_list, env_list) == FAILURE)
		return (FAILURE);
	cnt = pipe_cnt(word_list);
	get_fd_list(word_list, fd_list, cnt);
	if (cnt == 0 && is_builtin(word_list, &builtin_flg) == true)
	{
		if (in_output_operation(word_list, fd_list, env_list) == FAILURE)
			return (FAILURE);
		if (execve_builtin(word_list, env_list, *fd_list,
				builtin_flg) == FAILURE)
			return (FAILURE);
		if ((*fd_list)->here_file_name != NULL
			&& unlink((*fd_list)->here_file_name) < 0)
			return (put_cd_error_update_exit_status("unlink", env_list));
	}
	else
	{
		if (cnt == 0)
			cnt++;
		if (fork_execve_cmd(word_list, env_list, fd_list, cnt) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

void	init_minishell(char **envp,
					t_env_list **env_list_head,
					t_word_list **word_list_head,
					t_fd_list **fd_list)
{
	*word_list_head = NULL;
	*env_list_head = NULL;
	*fd_list = NULL;
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
	t_fd_list	*fd_list;
	char		*line;

	if (argc == 0 || argv == NULL)
		return (0);
	init_minishell(envp, &env_list_head, &word_head, &fd_list);
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
			read_word_list_execve_cmd(word_head, &env_list_head, &fd_list);
		}
		free(line);
		free_word_list(&word_head);
		free_fd_list(&fd_list);
	}
	free_env_list(&env_list_head);
	return (0);
}
