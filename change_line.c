/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:45:51 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/25 13:03:47 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/*この関数はstrをstr2にコピーして、strをfreeして結合時の長さにmallocしなおす。
次に頭からｋ文字までコピーし、さらにその先にadd_strを追加する関数*/
char *concate_str(char *str, char *add_str, int k)
{
	char	*str2;
	int		j;
	// int		len2;
	int 	i;

	str2 = str;
	// len1 = ft_strlen(str2);
	// len2 = ft_strlen(add_str);
	free(str);
	str = maloc(sizeof (char) * (k + ft_strlen(add_str) + 1));
	if (str == NULL)
		return (NULL);
	str[k + ft_strlen(add_str)] = '\0';
	i = 0;
	while (i < k || str2[i] != '\0')
	{
		str[i] == str2[i];
		i++;
	}
	while (add_str[j] != '\0')
	{
		str[i] == add_str[j];
		i++;
		j++;
	}
	return (str);
}

t_env_list *find_env_name(char *line, t_env_list *env_list, int i)
{
	
}

char *add_env(char *line, t_env_list *env_list, int i)
{
	t_env_list	*env_list2;

	env_list2 = env_list;
	env_list2 = find_env_name(line, env_list2, i);
	if (env_list2 == NULL)
		return (line);
	line = concate_str(line, env_list2->env_name, i);
	return (line);
}

char *change_line(char *line, t_env_list *env_list)
{
	int			i;
	char		*line2;
	t_env_list	*env_list2;

	i = 0;
	line2 = line;
	env_list2 = env_list;
	while (line2[i])
	{
		if (line2[i] == '$')
		{
			line2 = add_env(line2, env_list2, i);
			i = 0;
		}
		i++;
	}
	return (line);
}