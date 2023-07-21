/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:37:34 by reira             #+#    #+#             */
/*   Updated: 2023/07/21 17:58:55 by reira            ###   ########.fr       */
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

void	move_to_home(t_env_list *env_list)
{
	t_env_list	*node;

	node = NULL;
	ft_get_env("HOME", env_list, &node);
	if (node == NULL)
		put_error("cd: HOME not set\n", 0);
	if (chdir(node->env_str) < 0)
		put_error("chdir", 0);
}

void	move_to_oldpwd(t_env_list *env_list)
{
	t_env_list	*node;

	node = NULL;
	ft_get_env("OLDPWD", env_list, &node);
	if (node == NULL)
		put_error("cd: OLDPWD not set\n", NO_ERRNO);
	if (chdir(node->env_str) < 0)
		put_error("cd", 0);
}

void	cd_cmd(t_word_list **word_list, t_env_list *env_list)
{
	*word_list = (*word_list)->next;
	if (*word_list == NULL || ft_strcmp((*word_list)->word, "~") == 0)
		move_to_home(env_list);
	else if (ft_strcmp((*word_list)->word, "-") == 0)
		move_to_oldpwd(env_list);
	else
	{
		if (chdir((*word_list)->word) < 0)
			put_error("cd", 0);
	}
	if (*word_list != NULL && (*word_list)->flag != pipe_char)
		put_error("cd: too many arguments\n", NO_ERRNO);
}
