/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:47:56 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/28 02:21:00 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

int	pwd_cmd(int fd, t_env_list **env_list)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (put_cd_error_update_exit_status("getcwd", env_list));
	ft_putstr_fd(cwd, fd);
	ft_putstr_fd("\n", fd);
	free(cwd);
	return (SUCCESS);
}

static void	connect_env_list(t_env_list **env_list, t_env_list **new)
{
	if (*env_list == NULL)
		*env_list = *new;
	else if ((*env_list)->next == NULL)
		(*env_list)->next = *new;
	else
	{
		(*new)->next = (*env_list)->next;
		(*env_list)->next = *new;
	}
}

int	save_oldpwd(t_env_list **env_list)
{
	t_env_list	*head;
	t_env_list	*new;
	char		*join;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (put_cd_error_update_exit_status("getcwd", env_list));
	join = ft_strjoin("OLDPWD=", cwd);
	if (join == NULL)
		put_error_exit("failed to ft_strjoin");
	new_env_node(&new, join);
	if (new == NULL)
		put_error_exit("failed to new_env_node");
	head = *env_list;
	while (*env_list != NULL && (*env_list)->next != NULL
		&& ft_strcmp((*env_list)->env_name,
			"ORIGINAL_XDG_CURRENT_DESKTOP") != 0)
		*env_list = (*env_list)->next;
	connect_env_list(env_list, &new);
	*env_list = head;
	free(cwd);
	free(join);
	return (SUCCESS);
}
