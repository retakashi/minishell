/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:50:56 by reira             #+#    #+#             */
/*   Updated: 2023/07/16 15:05:55 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

extern t_shell			*g_shell_struct;

bool	should_putstr(t_word_list *head)
{
	if (head == NULL)
		return (false);
	if (head->flag == arguments || head->flag == option)
		return (true);
	return(false);
}

void	echo_cmd(t_word_list **word_list)
{
	int	opt_flg;

	opt_flg = 0;

	*word_list = (*word_list)->next;
	if (*word_list!=NULL&&ft_strcmp((*word_list)->word, "-n") == 0)
	{
		opt_flg = 1;
		*word_list = (*word_list)->next;
	}
	while (should_putstr(*word_list))
	{
		ft_putstr_fd((*word_list)->word, 1);
		if ((*word_list)->next != NULL && should_putstr((*word_list)->next))
			ft_putstr_fd(" ", 1);
		*word_list = (*word_list)->next;
	}
	if (opt_flg == 0)
		ft_putstr_fd("\n", 1);
}
