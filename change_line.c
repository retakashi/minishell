/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:45:51 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/25 21:07:35 by sraza            ###   ########.fr       */
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
	str = malloc(sizeof (char) * (k + ft_strlen(add_str) + 1));
	if (str == NULL)
		return (NULL);
	str[k + ft_strlen(add_str)] = '\0';
	i = 0;
	j = 0;
	while ( && (i < k || str2[i] != '\0'))
	{
		str[i] = str2[i];
		i++;
	}
	while (add_str[j] != '\0')
	{
		str[i] = add_str[j];
		i++;
		j++;
	}
	return (str);
}

t_env_list *find_env_name(char *line, t_env_list *env_list, int i)
{
	char	*content;
	int		j;
	int		k;

	while (i >= 0)
	{
		line++;
		i--;
	}
	while (line[i] != '\0' && line[i] != ' ')
		i++;
	printf(" %s : %i \n", line, i);
	content = malloc(sizeof (char) * (i + 1));
	content = duplicate(content, line, i);
	printf("===========     ++++=+++++++++++\n");
	k = ft_strlen(content);
	j = 0;
	while (env_list != NULL)
	{
		j = ft_strlen(env_list->env_name);
		printf("env_list->env_name =  %s ; content = %s \n", env_list->env_name, content);
		if (j < k)
			j = k;
		j = ft_strncmp(content, env_list->env_name, j);
		if (j == 0)
			return (env_list); 
		env_list = env_list->next;
	}
	return(env_list);
}

char *add_env(char *line, t_env_list *env_list, int i)
{
	t_env_list	*env_list2;

	env_list2 = env_list;
	env_list2 = find_env_name(line, env_list2, i);
	if (env_list2 == NULL)
		return (line);
	line = concate_str(line, env_list2->env_str, i);
	printf("new line is =  %s  \n", line);
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
			// i = 0;
			break ;
		}
		i++;
	}
	return (line);
}
