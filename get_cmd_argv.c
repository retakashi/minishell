/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:09:23 by reira             #+#    #+#             */
/*   Updated: 2023/07/31 17:07:16 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmd.h"
#include "libft/libft.h"

static bool	is_cmd_arg_flg(int flg)
{
	if (flg == command || flg == option || flg == arguments)
		return (true);
	return (false);
}

static int	cnt_cmd_argv(t_word_list *word_list)
{
	int	cnt;

	cnt = 0;
	while (word_list != NULL && word_list->flag != pipe_char)
	{
		if (word_list->flag == command || word_list->flag == option
			|| word_list->flag == arguments)
			cnt++;
		word_list = word_list->next;
	}
	return (cnt);
}

char	**get_cmd_argv(t_word_list *word_list, int *err_flg)
{
	char	**ans;
	int		cnt;
	int		i;

	cnt = cnt_cmd_argv(word_list);
	ans = ft_calloc(cnt + 1, sizeof(char *));
	if (ans == NULL)
		return (perror_change_err_flg("ft_calloc", err_flg));
	i = 0;
	while (i < cnt && word_list != NULL && word_list->flag != pipe_char)
	{
		if (is_cmd_arg_flg(word_list->flag) == true)
		{
			ans[i] = ft_strdup(word_list->word);
			if (ans[i] == NULL)
				return (perror_change_err_flg("ft_calloc", err_flg));
			i++;
		}
		word_list = word_list->next;
	}
	return (ans);
}
