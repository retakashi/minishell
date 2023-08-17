/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:14:41 by rtakashi          #+#    #+#             */
/*   Updated: 2023/08/17 14:53:03 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute_cmd.h"

static bool	is_valid_number(char *word, long long *num)
{
	size_t	i;
	int		error_flg;

	if (word[0] == '\0')
		return (false);
	i = 0;
	error_flg = 0;
	if (word[i] == '-' || word[i] == '+')
		i++;
	if (word[i] == '\0' || !ft_isdigit(word[i]))
		return (false);
	while (word[i] != '\0')
	{
		if (word[i] != '\0' && !ft_isdigit(word[i]))
			return (false);
		i++;
	}
	*num = ft_atoll(word, &error_flg);
	if (error_flg == 1)
		return (false);
	return (true);
}

static void	exit_end(t_word_list **word_list, t_env_list **env_list, int num,
		char *error_msg)
{
	if (error_msg == NULL && num == 0)
	{
		if (find_flg(*word_list, pipe_char) == false)
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		free_all_list(word_list, env_list, NULL);
		exit(EXIT_SUCCESS);
	}
	else if (error_msg != NULL)
	{
		exit_error(error_msg);
		free_all_list(word_list, env_list, NULL);
		exit(2);
	}
	if (find_flg(*word_list, pipe_char) == false)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	free_all_list(word_list, env_list, NULL);
	exit(num);
}

static int	exit_err_many_argument(t_env_list **env_list)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	update_exit_status(env_list, "1");
	return (FAILURE);
}

int	exit_cmd(t_word_list **word_list, t_env_list **env_list)
{
	long long	num;
	t_word_list	*head;

	head = *word_list;
	if ((*word_list)->next == NULL || (*word_list)->next->flag == pipe_char)
		exit_end(word_list, env_list, 0, NULL);
	num = 0;
	*word_list = (*word_list)->next;
	if (is_valid_number((*word_list)->word, &num) == false)
	{
		*word_list = head;
		exit_end(word_list, env_list, 0, (*word_list)->word);
	}
	if ((*word_list)->next != NULL && (*word_list)->next->flag != pipe_char)
	{
		*word_list = head;
		return (exit_err_many_argument(env_list));
	}
	if (num > 255 || num < -255)
		num = num % 256;
	if (num < 0)
		num += 256;
	*word_list = head;
	exit_end(word_list, env_list, (int)num, NULL);
	return (SUCCESS);
}
