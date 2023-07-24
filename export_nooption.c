/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_nooption.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:48:55 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/25 00:53:27 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

static void	init_write_flg(t_env_list **env_list)
{
	t_env_list	*head;

	head = *env_list;
	while (*env_list != NULL)
	{
		(*env_list)->write_flg = false;
		*env_list = (*env_list)->next;
	}
	*env_list = head;
}

static int	cnt_envp_list(t_env_list *env_list)
{
	int	cnt;

	if (env_list == NULL)
		return (0);
	cnt = 0;
	while (env_list != NULL)
	{
		cnt++;
		env_list = env_list->next;
	}
	return (cnt);
}

static void	write_env_exportver(t_env_list *env_list, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(env_list->env_name, fd);
	if (env_list->env_str != NULL)
	{
		ft_putstr_fd("=", fd);
		ft_putstr_fd("\"", fd);
		ft_putstr_fd(env_list->env_str, fd);
		ft_putstr_fd("\"", fd);
	}
	ft_putstr_fd("\n", fd);
}

static void	get_min(t_env_list **min, t_env_list *env_list)
{
	while (env_list != NULL && env_list->write_flg == true)
		env_list = env_list->next;
	*min = env_list;
}

int	export_nooption(t_env_list **env_list, int fd)
{
	int			cnt;
	t_env_list	*head;
	t_env_list	*min;

	if (env_list == NULL)
		return (env_error("export", env_list));
	cnt = cnt_envp_list(*env_list);
	head = *env_list;
	while (cnt > 0)
	{
		*env_list = head;
		get_min(&min, *env_list);
		while (*env_list != NULL)
		{
			if ((*env_list)->write_flg == false && ft_strcmp(min->env_name,
					(*env_list)->env_name) > 0)
				min = *env_list;
			*env_list = (*env_list)->next;
		}
		min->write_flg = true;
		write_env_exportver(min, fd);
		cnt--;
	}
	*env_list = head;
	return (SUCCESS);
}
