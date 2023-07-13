/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_write_envp_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:48:55 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/13 13:11:15 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

t_envp		*g_envp_list;

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	if (s1 == NULL)
		return ((unsigned char)s2[0] * -1);
	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	cnt_envp_list(void)
{
	t_envp	*head;
	int		cnt;

	head = g_envp_list;
	cnt = 0;
	while (head != NULL)
	{
		cnt++;
		head = head->next;
	}
	return (cnt);
}

static void	write_envp_export(void)
{
	write(1, "declare -x ", ft_strlen("declare -x "));
	write(1, g_envp_list->envp_name, ft_strlen(g_envp_list->envp_name));
	if (g_envp_list->envp_str != NULL)
	{
		write(1, "=", 1);
		write(1, "\"", 1);
		write(1, g_envp_list->envp_str, ft_strlen(g_envp_list->envp_str));
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

static void	sort_envp_list(int cnt_max)
{
	t_envp	*head;
	char	*max;
	t_envp	*max_node;

	head = g_envp_list;
	while (cnt_max > 0)
	{
		g_envp_list = head;
		max = NULL;
		while (g_envp_list != NULL)
		{
			if (g_envp_list->sort_num == 0 && ft_strcmp(max,
					g_envp_list->envp_name) < 0)
			{
				max_node = g_envp_list;
				max = max_node->envp_name;
			}
			g_envp_list = g_envp_list->next;
		}
		max_node->sort_num = cnt_max;
		cnt_max--;
	}
	g_envp_list = head;
}

void	export_nooption(void)
{
	int		i;
	int		cnt_max;
	t_envp	*head;

	i = 1;
	cnt_max = cnt_envp_list();
	sort_envp_list(cnt_max);
	head = g_envp_list;
	while (i <= cnt_max)
	{
		g_envp_list = head;
		while (g_envp_list != NULL)
		{
			if (g_envp_list->sort_num == i)
				write_envp_export();
			g_envp_list = g_envp_list->next;
		}
		i++;
	}
	g_envp_list = head;
}
