/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:10:19 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/06 15:34:48 by sraza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	ft_perror(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(str);
	return (FAILURE);
}

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


t_env_list	*init_minishell(char **envp, t_env_list **env_list_head)
{
	*env_list_head = NULL;
	if (envp != NULL)
		get_env_list(envp, env_list_head);
	return (*env_list_head);
}
