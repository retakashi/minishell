/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_2darr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:10:16 by reira             #+#    #+#             */
/*   Updated: 2023/08/09 17:42:51 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute_cmd.h"


static void	get_env_len(t_env_list *env_list, size_t *name_len, size_t *str_len)
{
	*name_len = ft_strlen(env_list->env_name);
	*str_len = ft_strlen(env_list->env_value);
}

static int	cnt_env_list(t_env_list *env_list)
{
	int	cnt;

	cnt = 0;
	while (env_list != NULL)
	{
		if (env_list->env_value != NULL)
			cnt++;
		env_list = env_list->next;
	}
	return (cnt);
}

static void	env_copy(char **ans, t_env_list *env_list, size_t name_len,
		size_t str_len)
{
	ft_strlcpy(*ans, env_list->env_name, name_len + 1);
	ft_strlcpy(*ans + name_len, "=", 2);
	ft_strlcpy(*ans + name_len + 1, env_list->env_value, str_len + 1);
}

// t_env_2d↓
// char	**ans;
// int		cnt;
// int		i;
// size_t	name_len;
// size_t	str_len;

char	**get_env_2darr(t_env_list *env_list, int *err_flg)
{
	t_env_2d	env_2d;

	env_2d.cnt = cnt_env_list(env_list);
	env_2d.ans = ft_calloc(env_2d.cnt + 1, sizeof(char *));
	if (env_2d.ans == NULL)
		return (perror_change_err_flg("ft_calloc", err_flg));
	env_2d.i = -1;
	while (++env_2d.i < env_2d.cnt)
	{
		if (env_list->env_name != NULL)
		{
			get_env_len(env_list, &env_2d.name_len, &env_2d.str_len);
			env_2d.ans[env_2d.i] = ft_calloc(env_2d.name_len + env_2d.str_len
				+ 2, sizeof(char));
			if (env_2d.ans[env_2d.i] == NULL)
				return (perror_change_err_flg("ft_calloc", err_flg));
			env_copy(&env_2d.ans[env_2d.i], env_list, env_2d.name_len,
				env_2d.str_len);
		}
		env_list = env_list->next;
	}
	return (env_2d.ans);
}
