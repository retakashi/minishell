/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_nooption.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:48:55 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/21 21:04:00 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	init_write_flg(t_env_list **env_list)
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

static void	write_env_exportver(t_env_list *env_list)
{
	write(1, "declare -x ", ft_strlen("declare -x "));
	write(1, env_list->env_name, ft_strlen(env_list->env_name));
	if (env_list->env_str != NULL)
	{
		write(1, "=", 1);
		write(1, "\"", 1);
		write(1, env_list->env_str, ft_strlen(env_list->env_str));
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

static void	get_min(t_env_list **min, t_env_list *env_list)
{
	while (env_list != NULL && env_list->write_flg == true)
		env_list = env_list->next;
	*min = env_list;
}

void	export_nooption(t_env_list *env_list)
{
	int			cnt;
	t_env_list	*head;
	t_env_list	*min;

	head = env_list;
	cnt = cnt_envp_list(env_list);
	while (cnt > 0)
	{
		env_list = head;
		get_min(&min, env_list);
		while (env_list != NULL)
		{
			if ((env_list)->write_flg == false && ft_strcmp(min->env_name,
					(env_list)->env_name) > 0)
				min = env_list;
			env_list = env_list->next;
		}
		min->write_flg = true;
		write_env_exportver(min);
		cnt--;
	}
}
