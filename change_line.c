/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:45:51 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/28 21:26:36 by sraza            ###   ########.fr       */
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

char	*copy_str(char *line, char **str, int k)
{
	int i;

	i = 0;
	while (*str[i] != '\0')
	{
		if (*str[i] == '\'')
		{
			line[i] = *str[i];
			i++;
			while (*str[i] != '\'' && *str[i] != '\0')
			{
				line[i] = *str[i];
				i++;	
			}
		}
		if (*str[i] == '$')
			break ;
		line[i] = *str[i];
		i++;
	}
	line[i] = '\0';
	while (k > 0)
	{
		str++;
		k--;
	}
	return (line);
}

char	*count_s_str(char **str)
{
	int		i;
	char	*line;

	i = 0;
	while (*str[i] != '\0')
	{
		if (*str[i] == '\'')
		{
			i++;
			while (*str[i] != '\'' || *str[i] != '\0')
				i++;
		}
		if (*str[i] == '$')
			break ;
		i++;
	}
	line = malloc (sizeof (char) * (i + 1));
	if (line == NULL)
		return (NULL);
	return (copy_str(line, str, i));
}

char	*count_d_str(char **str)
{
	int		i;
	char	*line;

	i = 0;
	while (*str[i] != ' ' && *str[i] != '\t' && *str[i] != '\0')
		i++;
	line = malloc (sizeof (char) * (i + 1));
	if (line == NULL)
		return (NULL);
	while (*str[i] != ' ' && *str[i] != '\t' && *str[i] != '\0')
		*line++ = **str++;
	*line = '\0';
	return (line);
}


char *make_strlist(char *line, t_env_list *env_list)
{
	char **max_str;
	int	i;
	// int j;

	i = 0;
	printf("count_env = %i, %s \n" ,(count_env_mark(line)), env_list->env_str);
	max_str = malloc(sizeof(char *) * (count_env_mark(line) * 2 + 1));
	if (max_str == NULL)
		return (NULL);
	while (*line != '\0')
	{
		if (*line != '$')
			max_str[i++] = count_s_str(&line);
		if (*line == '$')
			max_str[i++] = count_d_str(&line);
		if (*line == '\0')
			break ;
		line++;
	}
	max_str[i] = NULL;
	i = 0;
	while (max_str[i])
	{
		printf(" max_str[%i] = %s \n", i , max_str[i]);
		i++;
	}
	return (line);
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
