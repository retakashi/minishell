/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_word_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:02:28 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/14 22:07:02 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute_cmd.h"

volatile sig_atomic_t	g_sig;

bool	find_flg(t_word_list *word_list, int find_flg)
{
	while (word_list != NULL)
	{
		if (word_list->flag == find_flg)
			return (true);
		word_list = word_list->next;
	}
	return (false);
}

static int	cnt_pipe(t_word_list *word_list)
{
	int	cnt;

	cnt = 0;
	while (word_list != NULL)
	{
		while (word_list != NULL && word_list->flag != pipe_char)
			word_list = word_list->next;
		if (word_list != NULL && word_list->next != NULL
			&& word_list->flag == pipe_char)
			cnt++;
		while (word_list != NULL && word_list->flag == pipe_char)
			word_list = word_list->next;
	}
	return (cnt);
}

static void	advance_to_here_word_list(t_here_list **here_list,
										t_word_list **word_list,
										int flg)
{
	if (flg == true)
		*here_list = (*here_list)->next;
	if (*word_list != NULL)
		*word_list = (*word_list)->next;
}

static void	set_child_num(t_word_list *word_list, t_here_list **here_list)
{
	int			flg;
	int			i;
	t_here_list	*head;

	i = 0;
	head = *here_list;
	while (word_list != NULL && *here_list != NULL)
	{
		flg = false;
		while (word_list != NULL && word_list->flag != pipe_char)
		{
			if (flg == false && word_list->flag == heredoc)
			{
				(*here_list)->child_num = i;
				flg = true;
			}
			word_list = word_list->next;
		}
		i++;
		advance_to_here_word_list(here_list, &word_list, flg);
	}
	*here_list = head;
}

int	read_word_list(t_word_list **word_list, t_env_list **env_list,
		t_here_list **here_list)
{
	int		cnt;
	t_flg	flg_struct;

	if (*word_list == NULL)
		return (SUCCESS);
	if (find_flg(*word_list, eof_num) == true)
	{
		if (get_here_list(*word_list, here_list) == FAILURE)
			free_list_exit(word_list, env_list, here_list, EXIT_FAILURE);
		if (g_sig == SIGINT)
			return (update_exit_status(env_list, "130"));
	}
	cnt = cnt_pipe(*word_list);
	if (cnt == 0 && is_builtin(*word_list, &flg_struct.builtin_flg) == true)
		return (main_builtin(word_list, env_list, here_list, flg_struct));
	else
	{
		if (here_list != NULL)
			set_child_num(*word_list, here_list);
		if (main_execute_cmd(word_list, env_list, here_list, cnt) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
