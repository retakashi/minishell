/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:14:41 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/31 17:07:16 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "libft/libft.h"

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

static void	exit_end(t_word_list **word_list, t_env_list **env_list,
		int num, char *error_msg)
{
	if (error_msg == NULL && num == 0)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		free_all_list(word_list, env_list,NULL);
		exit(EXIT_SUCCESS);
	}
	else if (error_msg != NULL)
	{
		exit_error(error_msg);
		free_all_list(word_list, env_list,NULL);
		exit(2);
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	free_all_list(word_list, env_list,NULL);
	exit(num);
}

void	exit_cmd(t_word_list **word_list, t_env_list **env_list)
{
	long long	num;
	t_word_list	*head;
	char		*error_str;

	head = *word_list;
	if ((*word_list)->next == NULL||(*word_list)->next->flag==pipe_char)
		exit_end(word_list, env_list, 0, NULL);
	num = 0;
	*word_list = (*word_list)->next;
	if (is_valid_number((*word_list)->word, &num) == false)
	{
		error_str = (*word_list)->word;
		*word_list = head;
		exit_end(word_list, env_list, 0, error_str);
	}
	if (num > 255 || num < -255)
		num = num % 256;
	if (num < 0)
		num += 256;
	exit_end(word_list, env_list, (int)num, NULL);
}
