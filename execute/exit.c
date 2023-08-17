/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:14:41 by rtakashi          #+#    #+#             */
/*   Updated: 2023/08/18 02:36:05 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute_cmd.h"

static bool	is_valid_number(char *word, long long *num, char **str)
{
	size_t	i;
	int		error_flg;

	*num = 0;
	*str = word;
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
	if (error_msg != NULL)
		exit_error(error_msg);
	free_all_list(word_list, env_list, NULL);
	exit(num);
}

static void	put_exit(int pipe_flg)
{
	if (pipe_flg == false)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
}

static void	change_estatus(long long *num)
{
	if (*num > 255 || *num < -255)
		*num = *num % 256;
	if (*num < 0)
		*num += 256;
}

int	exit_cmd(t_word_list **word_list, t_env_list **env_list, int pipe_flg)
{
	long long	num;
	t_word_list	*head;
	char		*str;

	head = *word_list;
	str = NULL;
	if ((*word_list)->next == NULL || (*word_list)->next->flag == pipe_char)
	{
		put_exit(pipe_flg);
		exit_end(word_list, env_list, 0, NULL);
	}
	*word_list = (*word_list)->next;
	if (is_valid_number((*word_list)->word, &num, &str) == false)
	{
		put_exit(pipe_flg);
		*word_list = head;
		exit_end(word_list, env_list, 2, str);
	}
	if ((*word_list)->next != NULL && (*word_list)->next->flag != pipe_char)
		return (exit_err_many_argument(env_list, word_list, head));
	put_exit(pipe_flg);
	change_estatus(&num);
	*word_list = head;
	exit_end(word_list, env_list, (int)num, NULL);
	return (SUCCESS);
}
