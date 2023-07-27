/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_2darr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:10:16 by reira             #+#    #+#             */
/*   Updated: 2023/07/28 02:16:17 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"execve_cmd.h"
#include"libft/libft.h"

static void	get_env_len(t_env_list *env_list, size_t *name_len, size_t *str_len)
{
	if (env_list == NULL)
		return ;
	*name_len = ft_strlen(env_list->env_name);
	if (env_list->env_str == NULL)
		*str_len = 0;
	else
		*str_len = ft_strlen(env_list->env_str);
}

static int	cnt_env_list(t_env_list *env_list)
{
	int	cnt;

	cnt = 0;
	while (env_list != NULL)
	{
		env_list = env_list->next;
		cnt++;
	}
	return (cnt);
}

char	**get_env_2darr(t_env_list *env_list)
{
	char	**ans;
	int		cnt;
	int		i;
	size_t	name_len;
	size_t	str_len;
	
	if(env_list==NULL)
	return(NULL);
	cnt = cnt_env_list(env_list);
	ans = ft_calloc(cnt + 1, sizeof(char *));
	if (ans == NULL)
		put_error_exit("failed to get_envp_2darr");
	i = 0;
	while (i < cnt)
	{
		get_env_len(env_list, &name_len, &str_len);
		ans[i] = ft_calloc(name_len + str_len + 2, sizeof(char));
		if (ans[i] == NULL)
			put_error_exit("failed to get_envp_2darr");
		ft_strlcpy(ans[i], env_list->env_name, name_len + 1);
		ft_strlcpy(&ans[i][name_len], "=", 2);
		ft_strlcpy(&ans[i++][name_len + 1], env_list->env_str, str_len + 1);
		env_list = env_list->next;
	}
	return (ans);
}
