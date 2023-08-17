/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_noargs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:48:55 by rtakashi          #+#    #+#             */
/*   Updated: 2023/08/11 20:12:20 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute_cmd.h"

static void	init_write_flg(t_env_list **env_list)
{
	t_env_list	*head;

	head = *env_list;
	*env_list = (*env_list)->next;
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

	env_list = env_list->next;
	cnt = 0;
	while (env_list != NULL)
	{
		cnt++;
		env_list = env_list->next;
	}
	return (cnt + 1);
}

static void	get_min(t_env_list **min, t_env_list *env_list)
{
	while (env_list != NULL && env_list->write_flg == true)
		env_list = env_list->next;
	*min = env_list;
}

static void	init_export_noargs(t_env_list **env_list, t_env_list **head,
		int *cnt)
{
	*cnt = cnt_envp_list(*env_list);
	*head = *env_list;
	init_write_flg(env_list);
}

int	export_noargs(t_env_list **env_list, int fd)
{
	int			cnt;
	t_env_list	*head;
	t_env_list	*min;

	if ((*env_list)->next == NULL)
		return (env_error_update_exit_status("export", env_list));
	init_export_noargs(env_list, &head, &cnt);
	while (--cnt > 0)
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
	}
	*env_list = head;
	return (SUCCESS);
}
