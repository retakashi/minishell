/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:09:23 by reira             #+#    #+#             */
/*   Updated: 2023/07/26 15:10:56 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

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

char	**get_cmd_argv(t_word_list *word_list)
{
	char	**ans;
	int		cnt;
	int		i;

	cnt = cnt_cmd_argv(word_list);
	ans = ft_calloc(cnt + 1, sizeof(char *));
	if (ans == NULL)
		put_error_exit("failed to get_cmd_argv");
	i = 0;
	while (i < cnt && word_list != NULL && word_list->flag != pipe_char)
	{
		if (word_list->flag == command)
			ans[i] = ft_strdup(word_list->word);
		else if (word_list->flag == option)
			ans[i] = ft_strdup(word_list->word);
		else if (word_list->flag == arguments)
			ans[i] = ft_strdup(word_list->word);
		if ((word_list->flag == command || word_list->flag == option
				|| word_list->flag == arguments) && ans[i] == NULL)
			put_error_exit("failed to get_cmd_argv");
		if (ans[i] != NULL)
			i++;
		word_list = word_list->next;
	}
	return (ans);
}
