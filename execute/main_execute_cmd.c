/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execute_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:17:34 by reira             #+#    #+#             */
/*   Updated: 2023/08/20 19:36:58 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute_cmd.h"

static int	get_pipe_2darr(int ***pipe_2darr, int pipe_cnt)
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
			while (i > 0)
				free((*pipe_2darr)[i--]);
			free(*pipe_2darr);
			*pipe_2darr = NULL;
			return (ft_perror("malloc"));
		}
		i++;
	}
	return (SUCCESS);
}

// f_data↓
// 	int				**pipe_2darr;
// 	int					i;
// 	int					cnt;

int	main_execute_cmd(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list, int pipe_cnt)
{
	t_f_data	f_data;

	if (pipe_cnt == 0)
		return (execute_one_cmd(word_list, env_list, here_list));
	if (get_pipe_2darr(&f_data.pipe_2darr, pipe_cnt) == FAILURE)
		free_list_exit(word_list, env_list, here_list, EXIT_FAILURE);
	f_data.cnt = pipe_cnt;
	if (execute_some_cmds(word_list, env_list, here_list, f_data) == FAILURE)
		free_list_pipe2darr_exit(f_data, word_list, env_list, here_list);
	free_int_2darr(&f_data.pipe_2darr, f_data.cnt);
	return (SUCCESS);
}
