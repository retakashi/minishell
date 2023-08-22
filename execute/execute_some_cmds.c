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

#include "../execute_cmd.h"

static int	wait_some_cmds(pid_t pid)
{
	int	wstatus;

	if (waitpid(pid, &wstatus, 0) < 0)
		return (ft_perror("wait"));
	if (WIFSIGNALED(wstatus))
	{
		if (WTERMSIG(wstatus) == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3", STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		else if (WTERMSIG(wstatus) == SIGINT)
			ft_putstr_fd("\n", STDOUT_FILENO);
		return (128 + WTERMSIG(wstatus));
	}
	else
		return (WEXITSTATUS(wstatus));
}

static int	parent_close(t_f_data f_data)
{
	if (f_data.i > 0 && f_data.i <= f_data.cnt)
	{
		if (close(f_data.pipe_2darr[f_data.i - 1][READ]) < 0)
			return (ft_perror("close p"));
		if (close(f_data.pipe_2darr[f_data.i - 1][WRITE]) < 0)
			return (ft_perror("close p"));
	}
	return (SUCCESS);
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

static void	child_execute_cmds(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list, t_f_data f_data)
{
	t_child	c_data;

	advance_word_list(*word_list, &c_data.tmp_word, f_data.i);
	find_child_num(*here_list, &c_data.tmp_here, f_data.i);
	if (set_redirection(c_data.tmp_word, c_data.tmp_here, &c_data.fd_struct,
			&c_data.flg_struct.exit_flg) == FAILURE)
		free_list_pipe2darr_exit(f_data, word_list, env_list, here_list);
	if (find_flg_until_pipe(*word_list, command, f_data.i) == false)
		free_list_exit(word_list, env_list, here_list, EXIT_SUCCESS);
	free_here_list(here_list);
	dup2_pipe(f_data, word_list, env_list);
	close_pipe(f_data, word_list, env_list);
	free_int_2darr(&f_data.pipe_2darr, f_data.cnt);
	if (is_builtin(c_data.tmp_word, &c_data.flg_struct.builtin_flg) == true)
		execute_builtin_cmdsver(c_data, word_list, env_list);
	else
	{
		set_signal_child();
		if (dup2_fd_struct(c_data.fd_struct) == FAILURE)
			free_list_exit(word_list, env_list, NULL, EXIT_SUCCESS);
		prepare_execve_cmds(word_list, env_list, f_data.i);
	}
}

int	last_cmd_fork(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list, t_f_data *f_data)
{
	int		ret;
	char	*status;

	ret = 0;
	f_data->last_pid = fork();
	if (f_data->last_pid < 0)
		return (ft_perror("fork"));
	if (f_data->last_pid == 0)
		child_execute_cmds(word_list, env_list, here_list, *f_data);
	else
	{
		parent_close(*f_data);
		ret = wait_some_cmds(f_data->last_pid);
	}
	if (ret < 0)
		return (FAILURE);
	if (itoa_status(ret, &status) == FAILURE)
		return (FAILURE);
	update_exit_status(env_list, status);
	free(status);
	return (SUCCESS);
}

int	execute_some_cmds(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list, t_f_data f_data)
{
	f_data.i = -1;
	set_signal_parent();
	while (++f_data.i <= f_data.cnt)
	{
		if (f_data.i < f_data.cnt
			&& pipe(f_data.pipe_2darr[f_data.i]) == FAILURE)
			return (ft_perror("pipe"));
		if (f_data.i == f_data.cnt && last_cmd_fork(word_list, env_list,
				here_list, &f_data) < 0)
			return (FAILURE);
		else if (f_data.i < f_data.cnt)
		{
			f_data.pid = fork();
			if (f_data.pid < 0)
				return (ft_perror("fork"));
			if (f_data.pid == 0)
				child_execute_cmds(word_list, env_list, here_list, f_data);
			else
				parent_close(f_data);
		}
	}
	wait_some_cmds(f_data.pid);
	if (set_sigint() == FAILURE)
		return (ft_perror("failed to set signal"));
	return (SUCCESS);
}
