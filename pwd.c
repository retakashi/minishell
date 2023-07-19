/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:47:56 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/16 15:07:14 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

extern t_shell			*g_shell_struct;

void	pwd_cmd(t_word_list **word_list,t_env_list *env_list)
{
	t_env_list	*tmp;

	tmp = NULL;
	ft_get_env("PWD", env_list,&tmp);
	if (tmp == NULL)
		perror_exit("pwd", 0);
	write(1, tmp->env_str, ft_strlen(tmp->env_str));
	write(1, "\n", 1);
	while (*word_list != NULL && (*word_list)->flag != pipe_char)
		*word_list = (*word_list)->next;
}
