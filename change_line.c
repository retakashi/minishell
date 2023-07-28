/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:45:51 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/28 20:08:04 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


int	count_env_mark(char *line)
{
	int i;
	int count_env;

	i = 0;
	count_env = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
				i++;
		}
		if (line[i] == '$')
		{
			count_env++;
			while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
				i++;
			if (line[i] == '\0')
				break ;
		}
		i++;
	}
	return (count_env);
}

char	*copy_str(char *str)
{
	int		i;
	int		add_count;
	char	*line;

	i = 0;
	while (*str != '\0')
	{
		if (*str == '\'')
		{
			i++;
			while (*str != '\'' || *str != '\0')
				i++;
		}
	i++;
	}
	line = malloc ();
	add[i] = '\0';
	return (add);
}


char *make_strlist(char *line, t_env_list *env_list)
{
	char **max_str;
	int	i;
	int j;

	i = 0;
	printf("count_env = %i \n" ,(count_env_mark(line)));
	max_str = malloc(sizeof(char *) * (count_env_mark(line) * 2 + 1));
	if (max_str == NULL)
		return (NULL);
	while (*line != '\0')
	{
		if (*line != '$')
			max_str[i] = copy_str(line);
		// if (*line == '$')

		
	}


}


char *change_line(char *line, t_env_list *env_list)
{
	int i;
	char *new_line;

	i = 0;
	while (line[i] != '$' && line[i] != '\0')
		i++;
	if (i == (int)ft_strlen(line))
		return (line);
	new_line = make_strlist(line, env_list);
	
	printf("come here :%s \n %s\n", new_line, env_list->env_str);
	return (line);
}
