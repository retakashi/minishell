/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:37:34 by reira             #+#    #+#             */
/*   Updated: 2023/07/26 12:41:36 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "execve_cmd.h"

// cd - ~ . .. /
// cd only , cd ~ -> $HOME
// cd - ->$OLDPWD.

static int	move_to_home(t_env_list **env_list)
{
	t_env_list	*node;

	node = NULL;
	ft_get_env("HOME", *env_list, &node);
	if (node == NULL)
		return (put_error_update_exit_status("cd: HOME not set\n",env_list));
	if (chdir(node->env_str) < 0)
		return (put_error_update_exit_status("chdir", env_list));
	return (SUCCESS);
}

static int	move_to_oldpwd(t_env_list **env_list)
{
	t_env_list	*node;

	node = NULL;
	ft_get_env("OLDPWD", *env_list, &node);
	if (node == NULL)
		return (put_cd_error_update_exit_status("cd: OLDPWD not set\n", env_list));
	if (chdir(node->env_str) < 0)
		return (put_error_update_exit_status("chdir", env_list));
	return (SUCCESS);
}

int	cd_cmd(t_word_list *word_list, t_env_list **env_list)
{
	word_list = word_list->next;
	if (word_list == NULL)
		return (move_to_home(env_list));
	if (ft_strcmp(word_list->word, "~") == 0)
		return (move_to_home(env_list));
	else if (ft_strcmp(word_list->word, "-") == 0)
		return(move_to_oldpwd(env_list));
	if (chdir(word_list->word) < 0)
		return (put_error_update_exit_status(word_list->word, env_list));
	word_list = word_list->next;
	if (word_list != NULL && word_list->flag != pipe_char)
		return (put_error_update_exit_status("cd: too many arguments\n", env_list));
	return (SUCCESS);
}
