/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 20:44:30 by rtakashi          #+#    #+#             */
/*   Updated: 2023/08/11 23:26:45 by sraza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "minishell.h"

volatile sig_atomic_t	g_sig;

static void	init_minishell(char **envp, t_env_list **env_list_head,
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

static void	is_line_valid(void)
{
	if (errno == ENOMEM)
		exit(EXIT_FAILURE);
	else
	{
		ft_putstr_fd("minishell$ exit\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}

static void	free_success(char *line, t_word_list **word_list,
		t_here_list **here_list)
{
	if (line != NULL)
		free(line);
	if (*word_list != NULL)
		free_word_list(word_list);
	if (*here_list != NULL)
		free_here_list(here_list);
	*word_list = NULL;
	*here_list = NULL;
}

static void	loop_shell(t_main_data *data)
{
	while (1)
	{
		g_sig = 0;
		data->line = readline("minishell$ ");
		if (set_sigint() == FAILURE)
			exit(FAILURE);
		if (data->line == NULL)
			is_line_valid();
		if (g_sig == SIGINT)
			update_exit_status(&data->env_list, "130");
		data->new_line = change_line(data->line, data->env_list);
		data->word_list = parse_line(data->new_line);
		// if (data->word_list && check_error(data->word_list,
		// 		&data->env_list) == 0)
		// {
		// 	read_word_list(&data->word_list, &data->env_list, &data->here_list);
		// 	add_history(data->line);
		// 	free_success(data->line, &data->word_list, &data->here_list);
		// 	free(data->new_line);
		// }
		// else
		// 	free(data->word_list);
		if (data->word_list && check_error(data->word_list,
				&data->env_list) == 0)
			read_word_list(&data->word_list, &data->env_list, &data->here_list);
		add_history(data->line);
		free_success(data->line, &data->word_list, &data->here_list);
		free(data->new_line);

	}
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }

int	main(int argc, char **argv, char **envp)
{
	t_main_data	data;

	if (argc == 0 || argv == NULL)
		return (0);
	init_minishell(envp, &data.env_list, &data.word_list, &data.here_list);
	loop_shell(&data);
	free_env_list(&data.env_list);
	exit (EXIT_SUCCESS);
}
