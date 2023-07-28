/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:14:41 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/28 18:32:18 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
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

static void	free_list_builtin_exit(t_word_list **word_head, t_env_list **env_list,
		int num, char *error_msg)
{
	if (error_msg == NULL && num == 0)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		free_word_env_list(word_head, env_list);
		exit(EXIT_SUCCESS);
	}
	else if (error_msg != NULL)
	{
		exit_error(error_msg);
		free_word_env_list(word_head, env_list);
		exit(2);
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	free_word_env_list(word_head, env_list);
	exit(num);
}

void	exit_cmd(t_word_list *word_list, t_word_list *word_head,
		t_env_list **env_list)
{
	long long	num;

	if (word_list->next == NULL)
		free_list_builtin_exit(&word_head, env_list, 0, NULL);
	num = 0;
	word_list = word_list->next;
	if (is_valid_number(word_list->word, &num) == false)
		free_list_builtin_exit(&word_head, env_list, 0, word_list->word);
	if (num > 255 || num < -255)
		num = num % 256;
	if (num < 0)
		num += 256;
	free_list_builtin_exit(&word_head, env_list, (int)num, NULL);
}
