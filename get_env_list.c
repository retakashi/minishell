/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:40:13 by reira             #+#    #+#             */
/*   Updated: 2023/07/28 17:43:08 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

size_t	get_name_len(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0' && str[len] != '=')
		len++;
	return (len);
}

int	new_env_node(t_env_list **node, char *envp)
{
	size_t	len;

	*node = malloc(sizeof(t_env_list));
	if (*node == NULL)
		return (FAILURE);
	len = get_name_len(envp);
	(*node)->env_name = malloc(sizeof(char) * (len + 1));
	if ((*node)->env_name == NULL)
		return (FAILURE);
	ft_strlcpy((*node)->env_name, envp, len + 1);
	if (ft_strchr(envp, '='))
	{
		(*node)->env_str = ft_strdup(&envp[len + 1]);
		if ((*node)->env_str == NULL)
			return (FAILURE);
	}
	else
		(*node)->env_str = NULL;
	(*node)->write_flg = false;
	(*node)->exit_status = 0;
	(*node)->next = NULL;
	return (SUCCESS);
}

static int	new_node_noenvp(t_env_list **node)
{
	*node = malloc(sizeof(t_env_list));
	if (*node == NULL)
		return (FAILURE);
	(*node)->env_name = NULL;
	(*node)->env_str = NULL;
	(*node)->write_flg = false;
	(*node)->exit_status = 0;
	(*node)->next = NULL;
	return (SUCCESS);
}

int	get_env_list(char **envp, t_env_list **head)
{
	t_env_list	*new;
	t_env_list	*node;
	size_t		i;

	if (envp == NULL)
		return (new_node_noenvp(&node));
	if (new_env_node(&node, envp[0]) == FAILURE)
		return (FAILURE);
	*head = node;
	i = 1;
	while (envp[i] != NULL)
	{
		if (new_env_node(&new, envp[i]) == FAILURE)
			return (FAILURE);
		node->next = new;
		node = new;
		i++;
	}
	return (SUCCESS);
}
