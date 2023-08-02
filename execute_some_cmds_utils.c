/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_some_cmds_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:34:57 by reira             #+#    #+#             */
/*   Updated: 2023/08/03 02:11:11 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"execute_cmd.h"
#include"libft/libft.h"

void	advance_word_list(t_word_list *word_list, t_word_list **tmp, int start)
{
	int	i;

	*tmp = NULL;
	i = 0;
	while (i < start && word_list != NULL)
	{
		while (word_list != NULL && word_list->flag != pipe_char)
			word_list = word_list->next;
		if (word_list != NULL)
		{
			word_list = word_list->next;
			i++;
		}
	}
	*tmp = word_list;
}

void	find_child_num(t_here_list *here_list, t_here_list **tmp,
		int i)
{
	*tmp = NULL;
	while (here_list != NULL)
	{
		if (here_list->child_num == i)
			*tmp = here_list;
		here_list = here_list->next;
	}
}

bool find_flg_until_pipe(t_word_list *word_list, int find_flg,int cnt)
{
	int i;

	i=0;
	while(word_list!=NULL&&i<cnt)
	{
		if(word_list->flag==pipe_char)
		i++;
		word_list=word_list->next;
	}
	while(word_list!=NULL&&word_list->flag!=pipe_char)
	{
		if(word_list->flag==find_flg)
		return(true);
		word_list=word_list->next;
	}
	return(false);
}

void	execute_builtin_cmdsver(t_fd fd_struct, t_flg flg_struct,
		t_word_list **word_list, t_env_list **env_list)
{
	if (execute_builtin(*word_list, env_list, fd_struct, &flg_struct) == FAILURE
		|| flg_struct.exit_flg == true)
		free_list_exit(word_list, env_list, NULL, EXIT_FAILURE);
}
