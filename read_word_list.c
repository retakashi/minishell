/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_word_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:02:28 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/04 17:52:01 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "libft/libft.h"
#include "minishell.h"

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
		if (word_list->flag == pipe_char && word_list->next != NULL)
			cnt++;
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

void	set_child_num(t_word_list *word_list, t_here_list **here_list)
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

	if (find_flg(*word_list, eof_num) == true)
	{
		if (main_heredoc(word_list,
							here_list,
							env_list) == FAILURE)
			free_list_exit(word_list, env_list, here_list, EXIT_FAILURE);
		if (*here_list == NULL)
			return (SUCCESS);
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

void	init_minishell(char **envp, t_env_list **env_list_head,
		t_word_list **word_list_head, t_here_list **here_list)
{
	*word_list_head = NULL;
	*env_list_head = NULL;
	*here_list = NULL;
	set_signal_handler();
	if (get_env_list(envp, env_list_head) == FAILURE)
	{
		free_env_list(env_list_head);
		ft_perror("failed to get env list");
		exit(EXIT_FAILURE);
	}
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }

int	main(int argc, char **argv, char **envp)
{
	t_word_list	*word_head;
	t_env_list	*env_list_head;
	t_here_list	*here_list_head;
	char		*line;
	char		*new_line;

	if (argc == 0 || argv == NULL)
		return (0);
	init_minishell(envp, &env_list_head, &word_head, &here_list_head);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
		{
			if (errno == ENOMEM)
				exit(EXIT_FAILURE);
			else
			{
				ft_putstr_fd("minishell$ exit\n", STDOUT_FILENO);
				exit(EXIT_SUCCESS);
			}
		}
		if (*line)
		{
			// add_history(line);
			new_line = change_line(line, env_list_head);
			word_head = parse_line(new_line);
			set_signal_handler();
			read_word_list(&word_head, &env_list_head, &here_list_head);
		}
		free(line);
		free_word_list(&word_head);
		free_here_list(&here_list_head);
	}
	free_env_list(&env_list_head);
	return (0);
}
