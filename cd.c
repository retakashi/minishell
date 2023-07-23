/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:37:34 by reira             #+#    #+#             */
/*   Updated: 2023/07/23 22:04:34 by reira            ###   ########.fr       */
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

int	move_to_home(t_env_list **env_list)
{
	t_env_list	*node;

	node = NULL;
	ft_get_env("HOME", env_list, &node);
	if (node == NULL)
		return (put_error("cd: HOME not set\n", 0, env_list));
	if (chdir(node->env_str) < 0)
		return (put_error("chdir", 0, env_list));
	return (SUCCESS);
}

int	move_to_oldpwd(t_env_list **env_list)
{
	t_env_list	*node;

	node = NULL;
	ft_get_env("OLDPWD", env_list, &node);
	if (node == NULL)
		return (put_error("cd: OLDPWD not set\n", NO_ERRNO, env_list));
	if (chdir(node->env_str) < 0)
		return (put_error("chdir", 0, env_list));
	return (SUCCESS);
}

int	cd_cmd(t_word_list **word_list, t_env_list **env_list)
{
	*word_list = (*word_list)->next;
	if (*word_list == NULL)
		return (move_to_home(env_list));
	if (ft_strcmp((*word_list)->word, "~") == 0)
		return (move_to_home(env_list));
	else if (ft_strcmp((*word_list)->word, "-") == 0)
		reutrn(move_to_oldpwd(env_list));
	else
	{
		if (chdir((*word_list)->word) < 0)
			return (put_error((*word_list)->word, CD_ERROR, env_list));
	}
	*word_list = (*word_list)->next;
	if (*word_list != NULL && (*word_list)->flag != pipe_char)
		return (put_error("cd: too many arguments\n", NO_ERRNO, env_list));
	return (SUCCESS);
}
