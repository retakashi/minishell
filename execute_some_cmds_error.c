/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_some_cmds_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 23:37:44 by reira             #+#    #+#             */
/*   Updated: 2023/07/31 17:07:16 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "libft/libft.h"

void	put_pipe_error_exit(t_p_data p_data, t_word_list **word_list,
		t_env_list **env_list, t_here_list **here_list)
{
	ft_perror("pipe");
	unlink_here_list(here_list);
	free_list_pipe2darr_exit(p_data, word_list, env_list, here_list);
}

void	put_fork_error_exit(t_p_data p_data, t_word_list **word_list,
		t_env_list **env_list, t_here_list **here_list)
{
	ft_perror("fork");
	unlink_here_list(here_list);
	free_list_pipe2darr_exit(p_data, word_list, env_list, here_list);
}

void	put_error_exit_cmdsver(char *err_msg,t_p_data p_data, t_word_list **word_list,
		t_env_list **env_list)
{
	ft_perror(err_msg);
	free_list_pipe2darr_exit(p_data, word_list, env_list, NULL);
}
