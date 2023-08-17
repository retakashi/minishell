/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:50:57 by reira             #+#    #+#             */
/*   Updated: 2023/08/18 02:08:46 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute_cmd.h"

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

int	execute_builtin(t_word_list *word_list, t_env_list **env_list,
		t_fd fd_struct, t_flg *flg_struct)
{
	if (flg_struct->builtin_flg == echo_no)
		echo_cmd(word_list, fd_struct.out_fd);
	else if (flg_struct->builtin_flg == cd_no)
		return (cd_cmd(word_list, env_list));
	else if (flg_struct->builtin_flg == pwd_no)
		return (pwd_cmd(fd_struct.out_fd, env_list));
	else if (flg_struct->builtin_flg == export_no)
		return (export_cmd(word_list, env_list, fd_struct.out_fd,
				&flg_struct->exit_flg));
	else if (flg_struct->builtin_flg == unset_no)
		unset_cmd(word_list, env_list);
	else if (flg_struct->builtin_flg == env_no)
		return (env_cmd(env_list, fd_struct.out_fd));
	else if (flg_struct->builtin_flg == exit_no)
		return (exit_cmd(&word_list, env_list, flg_struct->pipe_flg));
	return (SUCCESS);
}

int	main_builtin(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list, t_flg flg_struct)
{
	t_fd	fd_struct;
	int		ret;
	int		e_ret;

	flg_struct.exit_flg = false;
	flg_struct.pipe_flg = false;
	ret = set_redirection(*word_list, *here_list, &fd_struct,
			&flg_struct.exit_flg);
	if (flg_struct.exit_flg == true)
		free_list_exit(word_list, env_list, here_list, EXIT_FAILURE);
	if (ret == FAILURE)
		return (update_exit_status(env_list, "1"));
	flg_struct.exit_flg = false;
	e_ret = execute_builtin(*word_list, env_list, fd_struct, &flg_struct);
	if (flg_struct.exit_flg == true)
		free_list_exit(word_list, env_list, here_list, EXIT_FAILURE);
	if (e_ret == SUCCESS)
		update_exit_status(env_list, "0");
	return (SUCCESS);
}
