/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:47:56 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/22 18:37:33 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	pwd_cmd(t_word_list **word_list,t_env_list *env_list)
{
	t_env_list	*tmp;

	tmp = NULL;
	ft_get_env("PWD", env_list,&tmp);
	if (tmp == NULL)
		put_error("pwd: PWD not set\n",NO_ERRNO);
	write(1, tmp->env_str, ft_strlen(tmp->env_str));
	write(1, "\n", 1);
	while (*word_list != NULL && (*word_list)->flag != pipe_char)
		*word_list = (*word_list)->next;
}
