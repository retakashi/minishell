/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:28:09 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/04 12:36:59 by sraza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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
