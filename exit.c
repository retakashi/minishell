/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:14:41 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/15 17:39:07 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	exit_cmd(t_word_list **word_list)
{
	if ((*word_list)->next==NULL)
		exit(EXIT_SUCCESS);
	*word_list=(*word_list)->next;
	g_shell_struct->exit_status = ft_atoi((*word_list)->word);
	exit(EXIT_SUCCESS);
}
