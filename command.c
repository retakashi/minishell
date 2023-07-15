/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:34:40 by reira             #+#    #+#             */
/*   Updated: 2023/07/16 01:24:29 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

bool	is_inequality_sign(int flag)
{
	if (flag == great || flag == great || flag == less || flag == less_less)
		return (true);
	return (false);
}

void	is_command(t_word_list **head)
{
	if (*head == NULL)
		return ;
	if ((*head)->flag == arguments)
		(*head)->flag = command;
	else if (is_inequality_sign((*head)->flag == true))
	{
		while ((*head != NULL && (*head)->next != NULL)
			&& (is_inequality_sign((*head)->flag) == true
				&& (*head)->next->flag == arguments))
			*head = (*head)->next->next;
		if ((*head)->flag == arguments)
			(*head)->flag = command;
	}
}

void	traverse_list_until_pipe(t_word_list **head)
{
	is_command(head);
	while (*head != NULL)
	{
		*head = (*head)->next;
		while (*head != NULL && (*head)->flag != pipe_char)
			*head = (*head)->next;
		if (*head == NULL)
			break ;
		else if ((*head)->next != NULL && (*head)->flag == pipe_char)
		{
			*head = (*head)->next;
			is_command(head);
		}
	}
	*head = g_shell_struct->word_head;
}

void	ft_get_env(char *str, t_env_list *env_list, t_env_list **tmp)
{
	if (env_list == NULL)
		return ;
	while (env_list != NULL && ft_strcmp(env_list->env_name, str) != 0)
		env_list = env_list->next;
	if (env_list != NULL && ft_strcmp(env_list->env_name, str) == 0)
		*tmp = env_list;
}

void	main_command(t_word_list *word_list,t_env_list *env_list)
{
	if (ft_strcmp(word_list->word, "echo") == 0)
		echo_cmd(&word_list);
	else if (ft_strcmp(word_list->word, "cd") == 0)
		cd_cmd(&word_list,env_list);
	else if (ft_strcmp(word_list->word, "pwd") == 0)
		pwd_cmd(&word_list,env_list);
	else if (ft_strcmp(word_list->word, "export") == 0)
		export_cmd(&word_list,&env_list);
	else if (ft_strcmp(word_list->word, "unset") == 0)
		unset_cmd(&word_list,&env_list);
	else if (ft_strcmp(word_list->word, "env") == 0)
		env_cmd(&word_list,env_list);
	else if (ft_strcmp(word_list->word, "exit") == 0)
		exit_cmd(&word_list);
	// else
	// 	other_command(&word_list,env_list);
	else 
	return;
}
