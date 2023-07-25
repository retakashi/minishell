/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:10:19 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/25 19:51:53 by sraza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

size_t get_name_len(char *str)
{
	size_t len;

	len=0;
	while (str[len] != '\0' && str[len] != '=')
		len++;
	return(len);
}

void	new_node(t_env_list **node, char *envp)
{
	size_t	len;

	*node = malloc(sizeof(t_env_list));
	len = get_name_len(envp);
	(*node)->env_name = malloc(sizeof(char) * (len + 1));
	strlcpy((*node)->env_name, envp, len + 1);
	if (strchr(envp, '='))
	{
		(*node)->env_str = strdup(&envp[len + 1]);
	}
	else
		(*node)->env_str = NULL;
	(*node)->write_flg = false;
	(*node)->exit_status=0;
	(*node)->next = NULL;
}

void	get_env_list(char **envp, t_env_list **head)
{
	t_env_list	*new;
	t_env_list	*node;
	size_t		i;

	new_node(&node, envp[0]);
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

t_env_list	*init_minishell(char **envp, t_env_list **env_list_head)
{
	// t_env_list *env_list;

	*env_list_head = NULL;
	if (envp != NULL)
		get_env_list(envp, env_list_head);
	// env_list = *env_list_head;
	// while (env_list != NULL)
	// {
	// 	printf("env_name = %s  \n env_str = %s\n\n", env_list->env_name, env_list->env_str);
	// 	env_list = env_list->next;
	// }
	return (*env_list_head);
}

// int main (int argc, char ** argv, char **env)
// {
// 	t_env_list *env_list;

// 	init_minishell(env, &env_list);
// 	while (env_list != NULL)
// 	{
// 		printf("env_name = %s  \n env_str = %s\n\n", env_list->env_name, env_list->env_str);
// 		env_list = env_list->next;
// 	}
// 	return(0);
// }