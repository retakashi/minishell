/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:34:40 by reira             #+#    #+#             */
/*   Updated: 2023/07/15 17:04:28 by reira            ###   ########.fr       */
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

void	ft_getenv(char *str, t_env_list *env_list, t_env_list **tmp)
{
	if (env_list == NULL)
		return ;
	while (env_list != NULL && ft_strcmp(env_list->env_name, str) != 0)
		env_list = env_list->next;
	if (env_list != NULL && ft_strcmp(env_list->env_name, str) == 0)
		*tmp = env_list;
}

void	main_command(t_word_list *head)
{
	if (ft_strcmp(head->word, "echo") == 0)
		echo_cmd();
	else if (ft_strcmp(head->word, "cd") == 0)
		cd_cmd();
	else if (ft_strcmp(head->word, "pwd") == 0)
		pwd_cmd();
	else if (ft_strcmp(head->word, "export") == 0)
		export_cmd();
	else if (ft_strcmp(head->word, "unset") == 0)
		unset_cmd();
	else if (ft_strcmp(head->word, "env") == 0)
		env_cmd();
	else if (ft_strcmp(head->word, "exit") == 0)
		exit_cmd();
	else
		command();
}
