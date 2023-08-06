/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:03:05 by reira             #+#    #+#             */
/*   Updated: 2023/07/31 17:13:08 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "libft/libft.h"

volatile sig_atomic_t	g_sig;

int	unlink_here_list(t_here_list **here_list)
{
	t_here_list	*head;

	if (here_list == NULL)
		return (SUCCESS);
	head = *here_list;
	while (*here_list != NULL)
	{
		if (unlink((*here_list)->here_file_name) < 0)
			return (ft_perror("unlink"));
		*here_list = (*here_list)->next;
	}
	*here_list = head;
	return (SUCCESS);
}

static int	parent_wait(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list)
{
	int	wstatus;

	// char *status;
	set_signal_parent();
	if (wait(&wstatus) < 0)
		free_list_exit(word_list, env_list, here_list, EXIT_FAILURE);
	if (set_sigint() == FAILURE)
		exit(FAILURE);
	if (WIFSIGNALED(wstatus))
		return (WTERMSIG(wstatus));
	else
		return (WEXITSTATUS(wstatus));
}

static void	prepare_execve(t_word_list **word_list, t_env_list **env_list)
{
	char	**env_2darr;
	char	**cmd_argv;
	int		err_flg;

	err_flg = false;
	env_2darr = get_env_2darr(*env_list, &err_flg);
	if (err_flg == true)
		free_list_exit(word_list, env_list, NULL, EXIT_FAILURE);
	cmd_argv = get_cmd_argv(*word_list, &err_flg);
	if (err_flg == true)
		free_list_exit(word_list, env_list, NULL, EXIT_FAILURE);
	free_all_list(word_list, env_list, NULL);
	execve_cmd(env_2darr, cmd_argv);
}

static void	child_execute(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list)
{
	t_fd	fd_struct;
	t_flg	flg_struct;

	flg_struct.exit_flg = false;
	if (set_redirection(*word_list, *here_list, &fd_struct,
			&flg_struct.exit_flg) == FAILURE)
		free_list_exit(word_list, env_list, here_list, EXIT_FAILURE);
	free_here_list(here_list);
	if (find_flg(*word_list, command) == false)
		free_list_exit(word_list, env_list, NULL, EXIT_SUCCESS);
	if (is_builtin(*word_list, &flg_struct.builtin_flg) == true)
	{
		if (execute_builtin(*word_list, env_list, fd_struct,
				&flg_struct) == FAILURE || flg_struct.exit_flg == true)
			free_list_exit(word_list, env_list, NULL, EXIT_FAILURE);
	}
	else
	{
		dup2_fd_struct(fd_struct, word_list, env_list);
		prepare_execve(word_list, env_list);
	}
}

int	execute_one_cmd(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list)
{
	pid_t	pid;
	int		ret;
	char	*status;

	ret = 0;
	pid = fork();
	if (pid < 0)
	{
		ft_perror("fork");
		free_list_exit(word_list, env_list, here_list, EXIT_FAILURE);
	}
	if (pid == 0)
		child_execute(word_list, env_list, here_list);
	else
		ret = parent_wait(word_list, env_list, here_list);
	if (ret == 2 || ret == 3)
		ret += 128;
	status = ft_itoa(ret);
	if (status == NULL)
		return (ft_perror("failed to ft_itoa"));
	update_exit_status(env_list, status);
	return (SUCCESS);
}
