/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:50:56 by reira             #+#    #+#             */
/*   Updated: 2023/07/13 18:03:16 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

bool	should_putstr(t_word_list *head)
{
	if (head == NULL)
		return (false);
	if (head->flag == arguments || head->flag == option)
		return (true);
	else
		perror_free_2d_arr_exit("newline", NULL, NULL, SYNTAX_ERROR);
}

void	echo_cmd(t_word_list **head)
{
	int	opt_flg;

	opt_flg = 0;
	if ((*head)->next == NULL)
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	*head = (*head)->next;
	if (*head != NULL && ft_strcmp((*head)->word, "-n") == 0)
	{
		if ((*head)->next == NULL)
			return ;
		opt_flg = 1;
		*head = (*head)->next;
	}
	while (should_putstr(*head))
	{
		ft_putstr_fd((*head)->word, 1);
		if ((*head)->next != NULL && should_putstr((*head)->next))
			ft_putstr_fd(" ", 1);
		*head = (*head)->next;
	}
	if (opt_flg == 0)
		ft_putstr_fd("\n", 1);
}
