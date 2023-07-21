/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 21:02:22 by reira             #+#    #+#             */
/*   Updated: 2023/07/21 21:12:09 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"


void	ft_get_env(char *str, t_env_list *env_list, t_env_list **tmp)
{
	if (env_list == NULL || str == NULL)
		return ;
	while (env_list != NULL && ft_strcmp(env_list->env_name, str) != 0)
		env_list = env_list->next;
	if (env_list != NULL && ft_strcmp(env_list->env_name, str) == 0)
		*tmp = env_list;
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	if (s1 == NULL)
		return ((unsigned char)s2[0] * -1);
	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	advance_to_inequality_sign_arg(t_word_list **word_list, int flag)
{
	while (*word_list != NULL && (*word_list)->flag != flag)
		*word_list = (*word_list)->next;
	*word_list = (*word_list)->next;
}
