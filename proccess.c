/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 22:37:50 by reira             #+#    #+#             */
/*   Updated: 2023/07/28 18:24:14 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

int	pipe_close(int *p_fd)
{
	if (close(p_fd[WRITE]) < 0)
		return (FAILURE);
	if (close(p_fd[READ]) < 0)
		return (FAILURE);
	return (SUCCESS);
}

void	search_here_list_child_num(t_here_list *here_list, t_here_list **tmp,
		t_proccess_data pro_data)
{
	*tmp = NULL;
	while (here_list != NULL)
	{
		if (here_list->child_num == pro_data.i)
			*tmp = here_list;
		here_list = here_list->next;
	}
}

int	in_output_file_dup2(t_fd fd_struct)
{
	if (fd_struct.in_fd != STDIN_FILENO && dup2(fd_struct.in_fd,
			STDIN_FILENO) < 0)
		return (FAILURE);
	if (fd_struct.out_fd != STDOUT_FILENO && dup2(fd_struct.out_fd,
			STDOUT_FILENO) < 0)
		return (FAILURE);
	return (SUCCESS);
}

void	first_execve_cmd(t_word_list *word_list, t_env_list **env_list,
		t_here_list *here_list, t_proccess_data pro_data)
{
	t_fd		fd_struct;
	t_flg		flg_struct;
	t_here_list	*tmp;

	search_here_list_child_num(here_list, &tmp, pro_data);
	if (in_output_operation(word_list, tmp, &fd_struct,&flg_struct.exit_error_flg ) == FAILURE)
		exit(EXIT_FAILURE);
	if (dup2(pro_data.pipe_2darr[0][WRITE], STDOUT_FILENO) < 0)
		put_error_exit("dup2");
	if (pipe_close(pro_data.pipe_2darr[0]) == FAILURE)
		put_error_exit("close");
	if (in_output_file_dup2(fd_struct) == FAILURE)
		put_error_exit("dup2");
	if (is_builtin(word_list, &flg_struct.builtin_flg) == true && execve_builtin(word_list,
			env_list, fd_struct, flg_struct) == FAILURE)
		get_cmdpath_execve(word_list, pro_data.env_2darr);
}

void	middle_execve_cmd(t_word_list *word_list, t_env_list **env_list,
		t_here_list *here_list, t_proccess_data pro_data)
{
	t_fd		fd_struct;
	t_flg flg_struct;
	t_here_list	*tmp;

	if(*env_list==NULL)
	return;
	search_here_list_child_num(here_list, &tmp, pro_data);
	if (in_output_operation(word_list, tmp, &fd_struct, &flg_struct.exit_error_flg) == FAILURE)
		exit(EXIT_FAILURE);
	if (dup2(pro_data.pipe_2darr[pro_data.i - 1][READ], STDIN_FILENO) < 0)
		put_error_exit("dup2");
	if (pipe_close(pro_data.pipe_2darr[pro_data.i - 1]) == FAILURE)
		put_error_exit("close");
	if (dup2(pro_data.pipe_2darr[pro_data.i][WRITE], STDOUT_FILENO) < 0)
		put_error_exit("dup2");
	if (pipe_close(pro_data.pipe_2darr[pro_data.i]) == FAILURE)
		put_error_exit("close");
	if (in_output_file_dup2(fd_struct) < 0)
		put_error_exit("dup2");
	get_cmdpath_execve(word_list, pro_data.env_2darr);
}

void	last_execve_cmd(t_word_list *word_list, t_env_list **env_list,
		t_here_list *here_list, t_proccess_data pro_data)
{
	t_fd		fd_struct;
	t_flg flg_struct;
	t_here_list	*tmp;

	if(*env_list==NULL)
	return;
	search_here_list_child_num(here_list, &tmp, pro_data);
	if (in_output_operation(word_list, tmp, &fd_struct, &flg_struct.exit_error_flg) == FAILURE)
		exit(EXIT_FAILURE);
	if (dup2(pro_data.pipe_2darr[pro_data.i - 1][READ], STDIN_FILENO) < 0)
		put_error_exit("dup2");
	if (pipe_close(pro_data.pipe_2darr[pro_data.i - 1]) == FAILURE)
		put_error_exit("close");
	if (in_output_file_dup2(fd_struct) == FAILURE)
		put_error_exit("dup2");
	get_cmdpath_execve(word_list, pro_data.env_2darr);
}

void	child_execve_cmd(t_word_list *word_list, t_env_list **env_list,
		t_here_list *here_list, t_proccess_data pro_data)
{
	if (pro_data.i == 0)
		first_execve_cmd(word_list, env_list, here_list, pro_data);
	else if (pro_data.i == pro_data.pipe_cnt)
		last_execve_cmd(word_list, env_list, here_list, pro_data);
	else
		middle_execve_cmd(word_list, env_list, here_list, pro_data);
}

void	parent(t_proccess_data pro_data)
{
	if (pro_data.i > 0 && pro_data.i <= pro_data.pipe_cnt)
	{
		if (close(pro_data.pipe_2darr[pro_data.i - 1][READ]) < 0)
			put_error_exit("close");
		if (close(pro_data.pipe_2darr[pro_data.i - 1][WRITE]) < 0)
			put_error_exit("close");
	}
}