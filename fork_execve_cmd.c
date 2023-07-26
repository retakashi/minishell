/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_execve_cmd_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:17:34 by reira             #+#    #+#             */
/*   Updated: 2023/07/26 18:59:42 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

void	in_output_operation_fork_ver(t_word_list *word_list,
									t_fd_list **fd_list)
{
	while (word_list != NULL && word_list->flag != pipe_char)
	{
		if (word_list->flag == input_file)
			(*fd_list)->in_fd = get_fd(word_list->word, input_file);
		else if (word_list->flag == output_file)
			(*fd_list)->out_fd = get_fd(word_list->word, output_file);
		else if (word_list->flag == append_file)
			(*fd_list)->out_fd = get_fd(word_list->word, append_file);
		else if (word_list->flag == heredoc)
			(*fd_list)->in_fd = get_fd((*fd_list)->here_file_name, heredoc);
		if ((*fd_list)->in_fd < 0 || (*fd_list)->out_fd < 0)
		{
			if ((*fd_list)->here_file_name != NULL
				&& unlink((*fd_list)->here_file_name) < 0)
				put_error_exit("unlink");
			put_error_exit("open");
		}
		word_list = word_list->next;
	}
	if ((*fd_list)->here_file_name != NULL
		&& unlink((*fd_list)->here_file_name) < 0)
		put_error_exit("unlink");
}

char	**extract_path_from_env_2darr(char **env_2darr)
{
	char	**ans;
	int		i;

	if (env_2darr == NULL)
		return (NULL);
	i = 0;
	while (env_2darr[i] != NULL && ft_strncmp("PATH=", env_2darr[i], 5) != 0)
		i++;
	if (env_2darr[i] == NULL)
		return (NULL);
	ans = ft_split(env_2darr[i], ':');
	if (ans == NULL)
		put_error_exit("failed to extract_path_from_env_2darr");
	ft_strlcpy(ans[0], &ans[0][5], ft_strlen(&ans[0][5]) + 1);
	return (ans);
}

void	get_cmdpath_execve(t_word_list *word_list, char **env_2darr)
{
	char	**path;
	char	**cmd_argv;
	int		i;
	char	*join_path;
	char	*join_cmd;

	path = extract_path_from_env_2darr(env_2darr);
	cmd_argv = get_cmd_argv(word_list);
	i = 0;
	while (path[i] != NULL)
	{
		join_path = ft_strjoin(path[i], "/");
		if (join_path == NULL)
			put_error_exit("failed to ft_strjoin");
		join_cmd = ft_strjoin(join_path, cmd_argv[0]);
		if (join_cmd == NULL)
			put_error_exit("failed to ft_strjoin");
		if (access(join_cmd, X_OK) == 0 && execve(join_cmd, cmd_argv,
				env_2darr) < 0)
			put_error_exit("execve");
		i++;
	}
	exit(EXIT_FAILURE);
}

void	child_execve_cmd(t_word_list *word_list, char **env_2darr,
		t_fd_list **fd_list, int p_fd[])
{
	in_output_operation_fork_ver(word_list, fd_list);
	printf("%d\n",p_fd[0]);
	printf("in_fd %d,out_fd %d\n", (*fd_list)->in_fd, (*fd_list)->out_fd);
	// if (dup2(p_fd[WRITE], STDOUT_FILENO) < 0)
	// 	put_error_exit("dup2");
	// if (close(p_fd[WRITE]) < 0)
	// 	put_error_exit("close");
	// if (close(p_fd[READ]) < 0)
	// 	put_error_exit("close");
	// if ((*fd_list)->in_fd != STDIN_FILENO && dup2((*fd_list)->in_fd,
	// 		STDIN_FILENO) < 0)
	// 	put_error_exit("dup2");
	// if ((*fd_list)->in_fd != STDIN_FILENO && close((*fd_list)->in_fd) < 0)
	// 	put_error_exit("close");
	// if ((*fd_list)->out_fd != STDOUT_FILENO && dup2((*fd_list)->out_fd,
	// 		STDOUT_FILENO) < 0)
	// 	put_error_exit("dup2");
	// if ((*fd_list)->out_fd != STDOUT_FILENO && close((*fd_list)->out_fd) < 0)
	// 	put_error_exit("close");
	get_cmdpath_execve(word_list, env_2darr);
}

int	parent(int p_fd[])
{
	printf("%d\n",p_fd[0]);
	// if (dup2(p_fd[READ], STDIN_FILENO) < 0)
	// 	put_error_exit("dup2");
	// if (close(p_fd[READ]) < 0)
	// 	put_error_exit("close");
	// if (close(p_fd[WRITE]) < 0)
	// 	put_error_exit("close");
	wait(NULL);
	 return(SUCCESS);
}

int	fork_execve_cmd(t_word_list *word_list, t_env_list **env_list,
		t_fd_list **fd_list, int pipe_cnt)
{
	int		p_fd[2];
	pid_t	pid;
	int		i;
	char	**env_2darr;
	int		builtin_flg;

	i = 0;
	env_2darr = get_envp_2darr(*env_list);
	while (i < pipe_cnt)
	{
		// if (pipe(p_fd) < 0)
		// 	put_error_exit("pipe");
		printf("p %d\n",p_fd[0]);
		printf("p %d\n",p_fd[1]);
		pid = fork();
		if (pid < 0)
			put_error_exit("fork");
		if (pid == 0 && is_builtin(word_list, &builtin_flg) == false)
			child_execve_cmd(word_list, env_2darr, fd_list, p_fd);
		// else if (pid == 0 && is_builtin(word_list, &builtin_flg) == true)
		// 	child_builtin(word_list, env_list, fd_list, p_fd);
		else
			parent(p_fd);
		i++;
		while (word_list != NULL && word_list->flag != pipe_char)
			word_list = word_list->next;
		if (word_list != NULL && word_list->flag == pipe_char)
			word_list = word_list->next;
		*fd_list = (*fd_list)->next;
	}
	return (SUCCESS);
}
