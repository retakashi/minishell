/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:14:31 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/02 21:09:54 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*joint_two_d(char *line, char *str, char *env_name, char *env_value)
{
	while (*str == *env_name)
	{
		str++;
		env_name++;
	}
	line = ft_strjoin(line, env_value);
	if (ft_isalnum(*str) || *str == '_')
		return (line);
	return (ft_strjoin(line, str));
}

char	*joint_d_str(char *line, char *str, t_env_list *env_list)
{
	if (*(str + 1) == '?')
		return (ft_strjoin(line, str));
	str = ft_strtrim(str, "$");
	while (env_list)
	{
		if (ft_strncmp(env_list->env_name, str,
				ft_strlen(env_list->env_name)) == 0)
		{
			if (ft_strlen(str) == ft_strlen(env_list->env_name))
				line = ft_strjoin(line, env_list->env_value);
			else
				line = joint_two_d(line, str, env_list->env_name,
						env_list->env_value);
			break ;
		}
		env_list = env_list->next;
	}
	return (line);
}

char	*joint_array(char **result, t_env_list *env_list)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (result[i] != NULL)
	{
		if (result[i][0] == '$')
		{
			line = joint_d_str(line, result[i], env_list);
			line = ft_strjoin(line, " ");
		}
		else if (result[i] != NULL && result[i][0] != '$')
			line = ft_strjoin(line, result[i]);
		i++;
	}
	return (line);
}

char	*change_line(char *line, t_env_list *env_list)
{
	int		i;
	char	**result;
	char	*new_line;

	i = 0;
	while (line[i] != '$' && line[i] != '\0')
		i++;
	if (i == (int)ft_strlen(line))
		return (line);
	result = make_strlist(line);
	new_line = joint_array(result, env_list);
	ft_free_line2(result);
	printf("new_line : %s \n ", new_line);
	return (new_line);
}
