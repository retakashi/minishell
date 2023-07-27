/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:50:57 by reira             #+#    #+#             */
/*   Updated: 2023/07/28 00:09:24 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

bool	is_builtin(t_word_list *word_list, int *builtin_flg)
{
	*builtin_flg = -1;
	while (word_list != NULL && word_list->flag != command)
		word_list = word_list->next;
	if (word_list != NULL && ft_strcmp(word_list->word, "echo") == 0)
		*builtin_flg = echo_no;
	else if (word_list != NULL && ft_strcmp(word_list->word, "cd") == 0)
		*builtin_flg = cd_no;
	else if (word_list != NULL && ft_strcmp(word_list->word, "pwd") == 0)
		*builtin_flg = pwd_no;
	else if (word_list != NULL && ft_strcmp(word_list->word, "export") == 0)
		*builtin_flg = export_no;
	else if (word_list != NULL && ft_strcmp(word_list->word, "unset") == 0)
		*builtin_flg = unset_no;
	else if (word_list != NULL && ft_strcmp(word_list->word, "env") == 0)
		*builtin_flg = env_no;
	else if (word_list != NULL && ft_strcmp(word_list->word, "exit") == 0)
		*builtin_flg = exit_no;
	if (*builtin_flg == -1)
		return (false);
	return (true);
}

static void	init_execve_builtin(t_word_list **word_list, t_fd *fd_struct)
{
	while (*word_list != NULL && (*word_list)->flag != command)
		*word_list = (*word_list)->next;
	fd_struct->in_fd = STDIN_FILENO;
	fd_struct->out_fd = STDOUT_FILENO;
}

int	execve_builtin(t_word_list *word_list, t_env_list **env_list,
		t_here_list *here_list, int builtin_flg)
{
	t_fd	fd_struct;

	init_execve_builtin(&word_list, &fd_struct);
	in_output_operation(word_list, here_list, &fd_struct, env_list);
	if (builtin_flg == echo_no && echo_cmd(word_list,
			fd_struct.out_fd) == FAILURE)
		return (FAILURE);
	else if (builtin_flg == cd_no && cd_cmd(word_list, env_list) == FAILURE)
		return (FAILURE);
	else if (builtin_flg == pwd_no && pwd_cmd(fd_struct.out_fd,
			env_list) == FAILURE)
		return (FAILURE);
	else if (builtin_flg == export_no)
		export_cmd(word_list, env_list, fd_struct.out_fd);
	else if (builtin_flg == unset_no)
		unset_cmd(word_list, env_list);
	else if (builtin_flg == env_no && env_cmd(env_list,
			fd_struct.out_fd) == FAILURE)
		return (FAILURE);
	else if (builtin_flg == exit_no)
		exit_cmd(word_list);
	return (SUCCESS);
}
