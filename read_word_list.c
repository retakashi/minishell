/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_word_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:02:28 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/06 16:32:01 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "libft/libft.h"
#include "minishell.h"

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
		if (word_list->flag == pipe_char && word_list->next != NULL)
			cnt++;
		word_list = word_list->next;
	}
	return (cnt);
}

static void	advance_to_here_word_list(t_here_list **here_list,
		t_word_list **word_list, int flg)
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
		if (get_here_list(*word_list, here_list) == FAILURE)
			free_list_exit(word_list, env_list, here_list, EXIT_FAILURE);
	}
	if (g_sig == SIGINT)
		return (SUCCESS);
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
	g_sig = 0;
	set_sigint();
	if (get_env_list(envp, env_list_head) == FAILURE)
	{
		free_env_list(env_list_head);
		ft_perror("failed to get env list");
		exit(EXIT_FAILURE);
	}
}

void	is_line_valid(void)
{
	if (errno == ENOMEM)
		exit(EXIT_FAILURE);
	else
	{
		ft_putstr_fd("minishell$ exit\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }

void	free_success(char *line, char *new_line, t_word_list **word_list,
		t_here_list **here_list)
{
	free(line);
	free(new_line);
	free_word_list(word_list);
	free_here_list(here_list);
}

int	main(int argc, char **argv, char **envp)
{
	t_main_data	data;

	if (argc == 0 || argv == NULL)
		return (0);
	init_minishell(envp, &data.env_list, &data.word_list, &data.here_list);
	while (1)
	{
		data.line = readline("minishell$ ");
		if (data.line == NULL)
			is_line_valid();
		if (g_sig == SIGINT)
			update_exit_status(&data.env_list, "130");
		// add_history(line);
		data.new_line = change_line(data.line, data.env_list);
		data.word_list = parse_line(data.new_line);
		read_word_list(&data.word_list, &data.env_list, &data.here_list);
		free_success(data.line, data.new_line, &data.word_list,
			&data.here_list);
	}
	free_env_list(&data.env_list);
	return (0);
}
