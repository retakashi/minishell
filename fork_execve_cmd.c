/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_execve_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:17:34 by reira             #+#    #+#             */
/*   Updated: 2023/07/30 02:15:31 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

int	get_pipe_2darr(int ***pipe_2darr, int pipe_cnt)
{
	int	i;

	*pipe_2darr = malloc(sizeof(int *) * (pipe_cnt));
	if (*pipe_2darr == NULL)
		return (ft_perror("malloc"));
	i = 0;
	while (i < pipe_cnt)
	{
		(*pipe_2darr)[i] = malloc(sizeof(int) * 2);
		if ((*pipe_2darr)[i] == NULL)
		{
			while ((*pipe_2darr)[i] != NULL)
				free((*pipe_2darr)[i++]);
			free(*pipe_2darr);
			*pipe_2darr = NULL;
			return (ft_perror("malloc"));
		}
		i++;
	}
	return (SUCCESS);
}

// typedef struct s_p_data
// {
// 	char				**pipe_2darr;
// 	int					i;
// 	int					cnt;
// }						t_p_data;

int	fork_execve_cmd(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list, int pipe_cnt)
{
	t_p_data	p_data;

	if (pipe_cnt == 0)
		return (execve_one_cmd(word_list, env_list, here_list));
	if (get_pipe_2darr(&p_data.pipe_2darr, pipe_cnt) == FAILURE)
		return (free_list_exit(word_list, env_list, here_list));
	p_data.cnt = pipe_cnt;
	execve_some_cmds(word_list, env_list, here_list, p_data);
	return (SUCCESS);
}
