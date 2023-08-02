/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:45:51 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/31 23:56:01 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	count_env_mark(char *line)
{
	int	i;
	int	count_env;

	i = 0;
	count_env = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
			count_env++;
		i++;
	}
	return (count_env);
}

char	*copy_str(char *line, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '$')
	{
		line[i] = str[i];
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i] != '\0')
			{
				line[i] = str[i];
				i++;
			}
			line[i] = str[i];
		}
		if (str[i] == '$')
			break ;
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*count_s_str(char **line)
{
	int		i;
	char	*str;

	i = 0;
	while ((*line)[i] != '\0')
	{
		if ((*line)[i] == '\'')
		{
			i++;
			while ((*line)[i] != '\'' && (*line)[i] != '\0')
				i++;
		}
		if ((*line)[i] == '$' || (*line)[i] == '\0')
			break ;
		i++;
	}
	str = malloc (sizeof (char) * (i + 1));
	if (str == NULL)
		return (NULL);
	str = copy_str(str, *line);
	(*line) += i;
	return (str);
}

char	*count_d_str(char **str)
{
	int		i;
	char	*line;

	i = 1;
	while ((*str)[i] != ' ' && (*str)[i] != '\t' &&
		(*str)[i] != '\0' && (*str)[i] != '$')
		i++;
	line = malloc (sizeof (char) * (i + 1));
	if (line == NULL)
		return (NULL);
	line[0] = (*str)[0];
	i = 1;
	while ((*str)[i] != ' ' && (*str)[i] != '\t' &&
		(*str)[i] != '\0' && (*str)[i] != '$')
	{
		line[i] = (*str)[i];
		i++;
	}
	(*str) += i;
	line[i] = '\0';
	return (line);
}

char	**make_strlist(char *line)
{
	char	**max_str;
	int		i;

	i = 0;
	max_str = malloc(sizeof(char *) * (count_env_mark(line) * 2 + 2));
	if (max_str == NULL)
		return (NULL);
	while (*line != '\0')
	{
		if (*line != '$' && *line != '\0')
		{
			max_str[i] = count_s_str(&line);
			i++;
		}
		if (*line == '$')
		{
			max_str[i] = count_d_str(&line);
			i++;
		}
		if (*line != '$' && *line != '\0')
			line++;
	}
	max_str[i] = NULL;
	i = 0;
	while (max_str[i])
	{
		printf("max_str[%i] = %s\n", i, max_str[i]);
		i++;
	}
	return (max_str);
}
