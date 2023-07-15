/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_nooption.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:48:55 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/16 01:12:40 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

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

void	export_nooption(t_env_list *env_list)
{
	int cnt;
	t_env_list *head;
	t_env_list *min;

	cnt = cnt_envp_list(env_list);
	head = env_list;
	min = env_list;
	while (cnt > 0)
	{
		env_list = head;
		while (env_list != NULL)
		{
			if (env_list->write_flg == false && ft_strcmp(min->env_name,
					env_list->env_name) < 0)
				min = env_list;
			env_list = env_list->next;
		}
		min->write_flg=true;
		write_env_exportver(min);
		cnt--;
	}
}
