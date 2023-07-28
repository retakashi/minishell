/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:50:57 by reira             #+#    #+#             */
/*   Updated: 2023/07/28 18:42:01 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

bool	is_builtin(t_word_list *word_list, int *builtin_flg)
{
	*builtin_flg = -1;
	while (word_list != NULL && word_list->flag != command)
		word_list = word_list->next;
	if (word_list == NULL)
		return (false);
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

static void	init_execve_builtin(t_word_list **word_list,
		t_word_list **word_head, int *exit_error_flg)
{
	*exit_error_flg = false;
	*word_head = *word_list;
	while (*word_list != NULL && (*word_list)->flag != command)
		*word_list = (*word_list)->next;
}

void	free_exit_builtinver(t_word_list *word_head, t_env_list **env_list)
{
	free_word_env_list(&word_head, env_list);
	exit(EXIT_FAILURE);
}

int	execve_builtin(t_word_list *word_list, t_env_list **env_list,
		t_fd fd_struct, t_flg flg_struct)
{
	t_word_list	*word_head;

	init_execve_builtin(&word_list, &word_head, &flg_struct.exit_error_flg);
	if (flg_struct.builtin_flg == echo_no)
		echo_cmd(word_list, fd_struct.out_fd);
	else if (flg_struct.builtin_flg == cd_no)
		return (cd_cmd(word_list, env_list));
	else if (flg_struct.builtin_flg == pwd_no)
		pwd_cmd(fd_struct.out_fd, &flg_struct.exit_error_flg);
	else if (flg_struct.builtin_flg == export_no)
		export_cmd(word_list, env_list, fd_struct.out_fd,
			&flg_struct.exit_error_flg);
	else if (flg_struct.builtin_flg == unset_no)
		unset_cmd(word_list, env_list);
	else if (flg_struct.builtin_flg == env_no)
		return (env_cmd(env_list, fd_struct.out_fd));
	else if (flg_struct.builtin_flg == exit_no)
		exit_cmd(word_list, word_head, env_list);
	if (flg_struct.exit_error_flg == true)
		free_exit_builtinver(word_head, env_list);
	return (SUCCESS);
}

int	main_builtin(t_word_list *word_list, t_env_list **env_list,
		t_here_list *here_list, t_flg flg_struct)
{
	t_fd	fd_struct;
	int		ret;

	ret = in_output_operation(word_list, here_list, &fd_struct,
		&flg_struct.exit_error_flg);
	free_here_list(&here_list);
	if (ret == FAILURE && flg_struct.exit_error_flg == true)
	{
		free_all_list(&word_list, env_list, &here_list);
		put_error_exit("failed to in_output operation");
	}
	if (ret == FAILURE && flg_struct.exit_error_flg == false)
		return (put_error_update_exit_status(word_list->word, env_list));
	execve_builtin(word_list, env_list, fd_struct, flg_struct);
	return (SUCCESS);
}
