/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:40:13 by reira             #+#    #+#             */
/*   Updated: 2023/08/11 20:15:59 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute_cmd.h"

size_t	get_name_len(char *str)
{
	size_t	len;

	len = 0;
	if (str == NULL)
		return (0);
	while (str[len] != '\0' && str[len] != '=')
		len++;
	return (len);
}

int	new_env_node(t_env_list **node, char *envp)
{
	size_t	len;

	*node = malloc(sizeof(t_env_list));
	if (*node == NULL)
		return (ft_perror("malloc"));
	len = get_name_len(envp);
	(*node)->env_name = malloc(sizeof(char) * (len + 1));
	if ((*node)->env_name == NULL)
		return (ft_perror("malloc"));
	ft_strlcpy((*node)->env_name, envp, len + 1);
	if (ft_strchr(envp, '='))
	{
		(*node)->env_value = ft_strdup(&envp[len + 1]);
		if ((*node)->env_value == NULL)
			return (ft_perror("ft_strdup"));
	}
	else
		(*node)->env_value = NULL;
	(*node)->write_flg = false;
	(*node)->next = NULL;
	return (SUCCESS);
}

static int	get_exit_status(t_env_list **node)
{
	*node = malloc(sizeof(t_env_list));
	if (*node == NULL)
		return (ft_perror("malloc"));
	(*node)->env_name = ft_strdup("exit_status");
	if ((*node)->env_name == NULL)
		return (ft_perror("ft_strdup"));
	(*node)->env_value = ft_strdup("0");
	if ((*node)->env_value == NULL)
		return (ft_perror("ft_strdup"));
	(*node)->write_flg = true;
	(*node)->next = NULL;
	return (SUCCESS);
}

int	get_env_list(char **envp, t_env_list **head)
{
	t_env_list	*new;
	t_env_list	*node;
	size_t		i;

	if (get_exit_status(&node) == FAILURE)
		return (FAILURE);
	if (envp == NULL)
		return (SUCCESS);
	*head = node;
	i = 0;
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
