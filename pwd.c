/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:47:56 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/15 17:44:04 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	pwd_cmd(t_env_list *env_list, t_word_list **word_list)
{
	t_env_list	*node;

	node = NULL;
	ft_getenvp("PWD", &node);
	if (node == NULL)
		perror_exit("pwd", 0);
	write(1, node->env_str, ft_strlen(node->env_str));
	write(1, "\n", 1);
	while (*word_list != NULL && (*word_list)->flag != pipe_char)
		*word_list = (*word_list)->next;
}
