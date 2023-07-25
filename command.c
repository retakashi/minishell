/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:34:40 by reira             #+#    #+#             */
/*   Updated: 2023/07/25 23:28:00 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

bool	is_inequality_sign(int flag)
{
	if (flag == output_file || flag == input_file || flag == append_file || flag == eof_num)
		return (true);
	return (false);
}

void	is_command(t_word_list **head)
{
	if (*head == NULL)
		return ;
	if ((*head)->flag == arguments)
		(*head)->flag = command;
	else if (is_inequality_sign((*head)->flag == true))
	{
		while ((*head != NULL && (*head)->next != NULL)
			&& (is_inequality_sign((*head)->flag) != true))
			*head = (*head)->next->next;
		if ((*head)->flag == arguments)
			(*head)->flag = command;
	}
}

void	get_command(t_word_list **head)
{
	t_word_list	*tmp;

	tmp = *head;
	is_command(head);
	while (*head != NULL)
	{
		*head = (*head)->next;
		while (*head != NULL && (*head)->flag != pipe_char)
			*head = (*head)->next;
		if ((*head) != NULL && (*head)->flag == pipe_char)
		{
			*head = (*head)->next;
			is_command(head);
		}
	}
	*head = tmp;
}

