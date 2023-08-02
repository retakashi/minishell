/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_some_c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 23:31:32 by reira             #+#    #+#             */
/*   Updated: 2023/07/30 00:55:34 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "libft/libft.h"

static void	parent_close(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list, t_p_data p_data)
{
	if (p_data.i > 0 && p_data.i <= p_data.cnt)
	{
		if (close(p_data.pipe_2darr[p_data.i - 1][READ]) < 0)
		{
			ft_perror("close");
			free_list_pipe2darr_exit(p_data, word_list, env_list, here_list);
		}
		if (close(p_data.pipe_2darr[p_data.i - 1][WRITE]) < 0)
		{
			ft_perror("close");
			free_list_pipe2darr_exit(p_data, word_list, env_list, here_list);
		}
	}
}

static void	wait_update_status(int cnt, t_word_list **word_list,
		t_env_list **env_list, t_here_list **here_list)
{
	int	wstatus;

	while (cnt-- >= 0)
	{
		if (wait(&wstatus) < 0)
		{
			ft_perror("wait");
			free_list_exit(word_list, env_list, here_list, EXIT_FAILURE);
		}
	}
	(*env_list)->env_value = ft_itoa(WEXITSTATUS(wstatus));
	if ((*env_list)->env_value == NULL)
	{
		ft_perror("ft_strdup");
		free_list_exit(word_list, env_list, here_list, EXIT_FAILURE);
	}
}

static void	prepare_execve_cmds(t_word_list **word_list, t_env_list **env_list,
		int start)
{
	char		**env_2darr;
	char		**cmd_argv;
	int			err_flg;
	t_word_list	*tmp;

	advance_word_list(*word_list, &tmp, start);
	err_flg = false;
	env_2darr = get_env_2darr(*env_list, &err_flg);
	if (err_flg == true)
		free_list_exit(word_list, env_list, NULL, EXIT_FAILURE);
	cmd_argv = get_cmd_argv(tmp, &err_flg);
	if (err_flg == true)
		free_list_exit(word_list, env_list, NULL, EXIT_FAILURE);
	free_all_list(word_list, env_list, NULL);
	execve_cmd(env_2darr, cmd_argv);
}

// t_child ↓
// 	t_fd				fd_struct;
// 	t_flg				flg_struct;
// 	t_here_list			*tmp_here;
// 	t_word_list			*tmp_word;

static void	child_execute_cmds(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list, t_p_data p_data)
{
	t_child	child;

	advance_word_list(*word_list, &child.tmp_word, p_data.i);
	find_child_num(*here_list, &child.tmp_here, p_data.i);
	if (set_redirection(child.tmp_word, child.tmp_here, &child.fd_struct,
			&child.flg_struct.exit_flg) == FAILURE)
		free_list_pipe2darr_exit(p_data, word_list, env_list, here_list);
	if (find_flg_until_pipe(*word_list, command, p_data.i) == false)
		free_list_exit(word_list, env_list, here_list, EXIT_SUCCESS);
	free_here_list(here_list);
	dup2_pipe(p_data, word_list, env_list);
	close_pipe(p_data, word_list, env_list);
	free_int_2darr(&p_data.pipe_2darr, p_data.cnt);
	if (is_builtin(child.tmp_word, &child.flg_struct.builtin_flg) == true)
		execute_builtin_cmdsver(child.fd_struct, child.flg_struct, word_list,
			env_list);
	else
	{
		dup2_fd_struct(child.fd_struct, word_list, env_list);
		prepare_execve_cmds(word_list, env_list, p_data.i);
	}
}

void	execute_some_cmds(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list, t_p_data p_data)
{
	pid_t	pid;

	p_data.i = 0;
	while (p_data.i <= p_data.cnt)
	{
		if (p_data.i < p_data.cnt && pipe(p_data.pipe_2darr[p_data.i]) < 0)
			put_pipe_error_exit(p_data, word_list, env_list, here_list);
		pid = fork();
		if (pid < 0)
			put_fork_error_exit(p_data, word_list, env_list, here_list);
		if (pid == 0)
			child_execute_cmds(word_list, env_list, here_list, p_data);
		else
			parent_close(word_list, env_list, here_list, p_data);
		p_data.i++;
	}
	wait_update_status(p_data.cnt, word_list, env_list, here_list);
}
