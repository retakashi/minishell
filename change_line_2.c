/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:14:31 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/29 17:58:25 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*joint_d_str(char *line, char *str, t_env_list *env_list)
{
	char	d;

	d = '\0';
	if (str[ft_strlen(str) - 1] == '"')
		d = '"';
	str = ft_strtrim(str, "$");
	str = ft_strtrim(str, "\"");
	while (env_list)
	{
		if (ft_strncmp(env_list->env_name, str, ft_strlen(env_list->env_name)) == 0)
		{
			if (d == '\0')
				line = ft_strjoin(line, env_list->env_str);
			else if (d != '\0')
			{
				line = ft_strjoin(line, env_list->env_str);
				line = ft_strjoin(line, "\"");
			}
			break ;
		}
		env_list = env_list->next;
	}
	// line = ft_strjoin(line, " ");
	return (line);
}

char *joint_array(char **result, t_env_list *env_list)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (result[i] != NULL)
	{
		if (result[i][0] == '$')
			line = joint_d_str(line, result[i], env_list);
		else if (result[i] != NULL && result[i][0] != '$')
		{
			line = ft_strjoin(line, result[i]);
			// line = ft_strjoin(line, result[i]);
		}
		i++;
	}
	return (line);
}

char *change_line(char *line, t_env_list *env_list)
{
	int i;
	char **result;
	char *new_line;

	i = 0;
	while (line[i] != '$' && line[i] != '\0')
		i++;
	if (i == (int)ft_strlen(line))
		return (line);
	result = make_strlist(line);
	new_line = joint_array(result, env_list);
	printf("new_line : %s \n ", new_line);
	return (new_line);
}