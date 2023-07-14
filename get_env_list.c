/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:40:13 by reira             #+#    #+#             */
/*   Updated: 2023/07/14 15:44:53 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

size_t	get_env_name(t_env_list **node, char *envp)
{
	size_t	len;

	if (envp == NULL)
		return (0);
	while (envp[len] != '\0' && envp[len] != '=')
		len++;
	(*node)->env_name = malloc(sizeof(char) * (len + 1));
	if ((*node)->env_name == NULL)
		perror_exit("malloc", 0);
	ft_strlcpy((*node)->env_name, envp, len + 1);
	return (len);
}

void	new_node(t_env_list **node, char *envp)
{
	size_t	name_len;

	*node = malloc(sizeof(t_env_list));
	if (*node == NULL)
		perror_exit("malloc", 0);
	name_len = get_env_name(node, envp);
	if (ft_strchr(envp, '='))
	{
		(*node)->env_str = ft_strdup(&envp[name_len + 1]);
		if ((*node)->env_str == NULL)
			perror_exit("ft_strdup", 0);
	}
	else
		(*node)->env_str = NULL;
	(*node)->sort_num = 0;
	(*node)->next = NULL;
}

void	get_env_list(char **envp, t_env_list **head)
{
	t_env_list	*new;
	t_env_list	*node;
	size_t		i;

	new_node(&node, envp[0]);
	g_shell_struct = node;
	*head = node;
	i = 1;
	while (envp[i] != NULL)
	{
		new_node(&new, envp[i]);
		node->next = new;
		node = new;
		i++;
	}
}
