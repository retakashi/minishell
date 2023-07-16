/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:49:05 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/16 14:42:52 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_env_list
{
	char				*env_name;
	char				*env_str;
	int					write_flg;
	bool				shell_variable;
	struct s_env_list	*next;
}						t_env_list;

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
	(*node)->shell_variable = false;
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

void	ft_get_env(char *str, t_env_list *env_list, t_env_list **tmp)
{
	if (env_list == NULL)
		return ;
	while (env_list != NULL && strcmp(env_list->env_name, str) != 0)
		env_list = env_list->next;
	if (env_list != NULL && strcmp(env_list->env_name, str) == 0)
		*tmp = env_list;
}

// __attribute__((destructor))
// void destrucor() {
// 	system("leaks a.out");
// }

int	main(int argc, char **argv, char **envp)
{
	t_env_list *head;
	t_env_list *tmp;
	
	get_env_list(envp, &head);
	ft_get_env("PATH", head, &tmp);	
	printf("tmp %s\n",tmp->env_name);
	printf("tmp %s\n",tmp->env_str);
	exit(0);
}
