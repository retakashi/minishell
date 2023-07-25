/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_execve_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:52:16 by reira             #+#    #+#             */
/*   Updated: 2023/07/26 00:02:03 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

// exit コマンドが子プロセスで実行された場合、シェル自体の終了ステータスは子プロセスの終了ステータスによって決定されます。
// 前述の例では、子プロセスの終了ステータスが「2」となるため、シェルの終了ステータスも「2」となります。

void	get_env_len(t_env_list *env_list, size_t *name_len, size_t *str_len)
{
	*name_len = ft_strlen(env_list->env_name);
	if (env_list->env_str == NULL)
		*str_len = 0;
	else
		*str_len = ft_strlen(env_list->env_str);
}

void	dup2_pipe_fd(int p_fd[2])
{
	if (dup2(p_fd[WRITE], STDOUT_FILENO) < 0)
		put_error_exit("dup2");
	if (close(p_fd[WRITE]) < 0)
		put_error_exit("close");
	if (close(p_fd[READ]) < 0)
		put_error_exit("close");
}

void	dup2_fd_list(t_fd_list *fd_list)
{
	if (fd_list->in_fd != STDIN_FILENO)
	{
		if (dup2(fd_list->in_fd, STDIN_FILENO) < 0)
			put_error_exit("dup2");
		if (close(fd_list->in_fd) < 0)
			put_error_exit("close");
	}
	if (fd_list->out_fd != STDOUT_FILENO)
	{
		if (dup2(fd_list->out_fd, STDOUT_FILENO) < 0)
			put_error_exit("dup2");
		if (close(fd_list->out_fd) < 0)
			put_error_exit("close");
	}
}

int	cnt_env_list(t_env_list *env_list)
{
	int	cnt;

	cnt = 0;
	while (env_list != NULL)
	{
		env_list = env_list->next;
		cnt++;
	}
	return (cnt);
}

char	**convert_env_list_to_2darr(t_env_list *env_list)
{
	char	**ans;
	int		cnt;
	int		i;
	size_t	name_len;
	size_t	str_len;

	i = 0;
	cnt = cnt_env_list(env_list);
	ans = ft_calloc(cnt + 1, sizeof(char *));
	if (ans == NULL)
		put_error_exit("failed to convert_env_list_to_2darr");
	while (i < cnt && env_list != NULL)
	{
		get_env_len(env_list, &name_len, &str_len);
		ans[i] = ft_calloc(name_len + str_len + 2, sizeof(char));
		if (ans[i] == NULL)
			put_error_exit("failed to convert_env_list_to_2darr");
		ft_strlcpy(ans[i], env_list->env_name, name_len + 1);
		ft_strlcpy(&ans[i][name_len], "=", 2);
		ft_strlcpy(&ans[i++][name_len + 1], env_list->env_str, str_len + 1);
		env_list = env_list->next;
	}
	return (ans);
}

int	cnt_argv(t_word_list *word_list)
{
	int	cnt;

	cnt = 0;
	while (word_list != NULL && word_list->flag != pipe_char)
	{
		if (word_list->flag == command || word_list->flag == option
			|| word_list->flag == arguments)
			cnt++;
		word_list = word_list->next;
	}
	return (cnt);
}

char	**get_comd_argv(t_word_list *word_list)
{
	char	**ans;
	int		cnt;
	int		i;
	size_t	len;

	cnt = cnt_argv(word_list);
	ans = ft_calloc(cnt + 1, sizeof(char *));
	if (ans == NULL)
		put_error_exit("failed to get_cmd_argv");
	i = 0;
	while (i < cnt && word_list != NULL && word_list->flag != pipe_char)
	{
		if (word_list->flag == command || word_list->flag == option
			|| word_list->flag == arguments)
		{
			len = ft_strlen(word_list->word) + 1;
			ans[i] = ft_calloc(len, sizeof(char));
			if (ans[i] == NULL)
				put_error_exit("failed to get_cmd_argv");
			ft_strlcpy(ans[i++], word_list->word, len);
		}
		word_list = word_list->next;
	}
	return (ans);
}

char	**get_envp_path(char **envp)
{
	char	**e_path;
	size_t	i;

	i = 0;
	e_path = NULL;
	if (envp == NULL)
		return (NULL);
	while (envp[i] != NULL && ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	e_path = ft_split(envp[i], ':');
	if (e_path == NULL)
		put_error_exit("failed to get_envp_path");
	ft_strlcpy(e_path[0], &e_path[0][5], ft_strlen(&e_path[0][5]) + 1);
	return (e_path);
}

void	execve_cmd(t_word_list *word_list, t_env_list **env_list)
{
	t_execve_struct	e_struct;

	e_struct.i = 0;
	e_struct.envp = convert_env_list_to_2darr(*env_list);
	e_struct.argv = get_comd_argv(word_list);
	e_struct.env_path = get_envp_path(e_struct.envp);
	while (e_struct.env_path[e_struct.i++] != NULL)
	{
		e_struct.path = ft_strjoin(e_struct.env_path[e_struct.i], "/");
		if (e_struct.path == NULL)
			put_error_exit("failed to ft_strjoin");
		e_struct.cmd_path = ft_strjoin(e_struct.path, e_struct.argv[0]);
		if (e_struct.cmd_path == NULL)
			put_error_exit("failed to ft_strjoin");
		if (access(e_struct.cmd_path, X_OK) == 0 && execve(e_struct.cmd_path,
				e_struct.argv, e_struct.envp) < 0)
			put_error_exit("execve");
	}
	free(e_struct.path);
	free(e_struct.cmd_path);
	command_error(e_struct.argv[0], env_list);
	exit(EXIT_FAILURE);
}

void	child(t_word_list *word_list, t_env_list **env_list, t_fd_list *fd_list,
		int p_fd[2])
{
	int	builtin_flg;
	dup2_pipe_fd(p_fd);
	if (in_output_operation(word_list, &fd_list, env_list) == FAILURE)
		exit(EXIT_FAILURE);
	while (word_list != NULL && word_list->flag != command)
		word_list = word_list->next;
	if (word_list == NULL)
		exit(SUCCESS);
	if (is_builtin(word_list, &builtin_flg) == true)
	{
		if (execve_builtin(word_list, env_list, fd_list,
				builtin_flg) == FAILURE)
			exit(EXIT_FAILURE);
		else
			exit(SUCCESS);
	}
	dup2_fd_list(fd_list);
	if (word_list != NULL && word_list->flag == command)
		execve_cmd(word_list, env_list);
}

void	parent(int p_fd[])
{
	if (dup2(p_fd[READ], STDIN_FILENO) < 0)
		put_error_exit("dup2");
	if (close(p_fd[WRITE]) < 0)
		put_error_exit("close");
	if (close(p_fd[READ]) < 0)
		put_error_exit("close");
}

int	fork_execve_cmd(t_word_list *word_list, t_env_list **env_list,
		t_fd_list *fd_list, int pipe_cnt)
{
	int		p_fd[2];
	pid_t	pid;
	int		i;

	i = 0;
	if (i < pipe_cnt)
	{
		if (pipe(p_fd) < 0)
			return (put_error_update_exit_status("pipe", env_list));
		pid = fork();
		if (pid < 0)
			return (put_error_update_exit_status("fork", env_list));
		if (pid == 0)
			child(word_list, env_list, fd_list, p_fd);
		else
			parent(p_fd);
		i++;
		while (word_list != NULL && word_list->flag != pipe_char)
			word_list = word_list->next;
		if (word_list != NULL)
			word_list = word_list->next;
		fd_list=fd_list->next;
	}
	while (i < pipe_cnt)
	{
		if (wait(NULL) < 0)
			put_error_exit("wait");
	}
	return (SUCCESS);
}
