/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:37:34 by reira             #+#    #+#             */
/*   Updated: 2023/07/13 20:34:09 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

// cd - ~ . .. /
// cdのみ , cd ~ -> $HOME
// If DIR is "-", it is converted to $OLDPWD.
//chdir -> "-" "~" は使えない
// argv[0]==cd
//チルダプレフィックスが `~+' ならば、チルダプレフィックスはシェル変数 PWD の値
//チルダプレフィックスが `~-' ならば、シェル変数 OLDPWD の値

void	move_to_home(t_word_list **head)
{
	t_envp	*node;

	node = NULL;
	ft_getenvp("HOME", &node);
	if (node == NULL || node->envp_str == NULL)
		perror_free_2d_arr_exit("cd", NULL, NULL, NULL);
	if (chdir(node->envp_str) < 0)
		perror_free_2d_arr_exit("chdir", NULL, NULL, NULL);
	while (*head != NULL || (*head)->flag != pipe_char)
	{
		*head = (*head)->next;
		if ((*head)->flag != arguments && (*head)->flag != option)
			perror_free_2d_arr_exit("newline", NULL, NULL, SYNTAX_ERROR);
	}
}

void	move_to_oldpwd(t_word_list **head)
{
	t_envp	*node;

	ft_getenvp("OLDPWD", &node);
	if (*head != NULL)
		*head = (*head)->next;
	if (node == NULL || node->envp_str == NULL)
		perror_free_2d_arr_exit("cd", NULL, NULL, NULL);
	if (chdir(node->envp_str) < 0)
		perror_free_2d_arr_exit("chdir", NULL, NULL, NULL);
}

void	cd_cmd(t_word_list **head)
{
	*head = (*head)->next;
	if (*head == NULL || ft_strcmp((*head)->word, "~") == 0)
		move_to_home(head);
	else if (*head == NULL || ft_strcmp((*head)->word, "-") == 0)
		move_to_oldpwd(head);
	else
	{
		if (chdir((*head)->word) < 0)
			perror_free_2d_arr_exit("chdir", NULL, NULL, NULL);
	}
}
