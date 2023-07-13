/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:40:13 by reira             #+#    #+#             */
/*   Updated: 2023/07/13 16:49:19 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

t_envp	*g_envp_list;

size_t	get_envp_name(t_envp **node, char *envp)
{
	size_t	len;

	if (envp == NULL)
		return (0);
	while (envp[len] != '\0' && envp[len] != '=')
		len++;
	(*node)->envp_name = malloc(sizeof(char) * (len + 1));
	if ((*node)->envp_name == NULL)
		perror_free_2d_arr_exit("malloc", NULL, NULL, NULL);
	ft_strlcpy((*node)->envp_name, envp, len + 1);
	return (len);
}

void	new_node(t_envp **node, char *envp)
{
	size_t	name_len;

	*node = malloc(sizeof(t_envp));
	if (*node == NULL)
		perror_free_2d_arr_exit("malloc", NULL, NULL, NULL);
	name_len = get_envp_name(node, envp);
	if (ft_strchr(envp, '='))
	{
		(*node)->envp_str = ft_strdup(&envp[name_len + 1]);
		if ((*node)->envp_str == NULL)
			perror_free_2d_arr_exit("ft_strdup", NULL, NULL, NULL);
	}
	else
		(*node)->envp_str = NULL;
	(*node)->sort_num = 0;
	(*node)->fd_struct->here_fd = 0;
	(*node)->fd_struct->in_fd = 0;
	(*node)->fd_struct->out_fd = 0;
	(*node)->fd_struct->pipe_fd[0] = 0;
	(*node)->fd_struct->pipe_fd[1] = 0;
	(*node)->next = NULL;
}

void	get_envp_list(char **envp)
{
	t_envp	*new;
	t_envp	*node;
	size_t	i;

	g_envp_list->envp_2d_arr = envp;
	new_node(&node, envp[0]);
	g_envp_list = node;
	i = 1;
	while (envp[i] != NULL)
	{
		new_node(&new, envp[i]);
		node->next = new;
		node = new;
		i++;
	}
}
