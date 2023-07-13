/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:37:41 by reira             #+#    #+#             */
/*   Updated: 2023/07/13 19:31:35 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

// "\" ";"の解釈は必要なし

void	ft_getenvp(char *str, t_envp **node)
{
	t_envp	*head;

	head = g_envp_list;
	while (g_envp_list != NULL && ft_strcmp(g_envp_list->envp_name, str) != 0)
		g_envp_list = g_envp_list->next;
	if (g_envp_list != NULL && ft_strcmp(g_envp_list->envp_name, str) == 0)
		*node = g_envp_list;
	g_envp_list = head;
}

bool	is_builtin(t_word_list *head)
{
	if (ft_strcmp(head->word, "echo") == 0)
		g_envp_list->builtin_flg = echo_no;
	else if (ft_strcmp(head->word, "cd") == 0)
		g_envp_list->builtin_flg = cd_no;
	else if (ft_strcmp(head->word, "pwd") == 0)
		g_envp_list->builtin_flg = pwd_no;
	else if (ft_strcmp(head->word, "export") == 0)
		g_envp_list->builtin_flg = export_no;
	else if (ft_strcmp(head->word, "unset") == 0)
		g_envp_list->builtin_flg = unset_no;
	else if (ft_strcmp(head->word, "env") == 0)
		g_envp_list->builtin_flg = env_no;
	else if (ft_strcmp(head->word, "exit") == 0)
		g_envp_list->builtin_flg = exit_no;
	else
		return (false);
	return (true);
}

void	main_builtin(t_word_list **head)
{
	if (g_envp_list->builtin_flg == echo_no)
		echo_cmd(head);
	else if (g_envp_list->builtin_flg == cd_no)
		cd_cmd(head);
	else if (g_envp_list->builtin_flg == pwd_no)
		pwd_cmd(head);
	else if (g_envp_list->builtin_flg == export_no)
		export_cmd(head);
	else if (g_envp_list->builtin_flg == unset_no)
		unset_cmd(head);
	else if (g_envp_list->builtin_flg == env_no)
		env_cmd(head);
	else if (g_envp_list->builtin_flg == exit_no)
		exit_cmd(head);
}
