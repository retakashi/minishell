/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_one_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:03:05 by reira             #+#    #+#             */
/*   Updated: 2023/07/30 22:55:46 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

static void	parent_wait(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list)
{
	int	wstatus;

	if (wait(&wstatus) < 0)
		free_list_exit(word_list, env_list, here_list,EXIT_FAILURE);
	(*env_list)->exit_status = WIFEXITED(wstatus);
}

void	prepare_execve_cmd(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list)
{
	char	**env_2darr;
	char	**cmd_argv;
	int		err_flg;

	err_flg = false;
	env_2darr = get_env_2darr(*env_list, &err_flg);
	if (err_flg == true)
		free_list_exit(word_list, env_list, here_list,EXIT_FAILURE);
	cmd_argv = get_cmd_argv(*word_list, &err_flg);
	if (err_flg == true)
		free_list_exit(word_list, env_list, here_list,EXIT_FAILURE);
	free_all_list(word_list, env_list, here_list);
	execve_cmd(env_2darr, cmd_argv);
}

static void	child_execve(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list)
{
	t_fd	fd_struct;
	t_flg	flg_struct;

	flg_struct.exit_flg = false;
	if (in_output_operation(*word_list, *here_list, &fd_struct,
			&flg_struct.exit_flg) == FAILURE)
		free_list_exit(word_list, env_list, here_list,EXIT_FAILURE);
	if (is_word_list_flag(*word_list, command) == false)
		free_list_exit(word_list, env_list, here_list,EXIT_SUCCESS);
	if (is_builtin(*word_list, &flg_struct.builtin_flg) == true)
	{
		if (execute_builtin(*word_list, env_list, fd_struct,
				&flg_struct) == FAILURE || flg_struct.exit_flg == true)
			free_list_exit(word_list, env_list, here_list,EXIT_FAILURE);
	}
	else
	{
		in_out_file_dup2(fd_struct, word_list, env_list, here_list);
		prepare_execve_cmd(word_list, env_list, here_list);
	}
}

int	execve_one_cmd(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror_free_list_exit("fork", word_list, env_list, here_list);
	if (pid == 0)
		child_execve(word_list, env_list, here_list);
	else
		parent_wait(word_list, env_list, here_list);
	return (SUCCESS);
}
