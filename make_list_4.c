/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:58:42 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/28 20:51:48 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"execve_cmd.h"
#include"libft/libft.h"
t_word_list	*argument_flag(t_word_list *string)
{
	t_word_list	*tmp;

	tmp = string;
	while (tmp != NULL)
	{
		tmp->flag = 0;
		tmp = tmp->next;
	}
	tmp = string;
	while (tmp != NULL)
	{
		if (tmp->word != NULL && (tmp->word[0] == '"' || tmp->word[0] == '\''))
			tmp->flag = 3;
		tmp = tmp->next;
	}
	return (string);
}
