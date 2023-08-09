/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:28:09 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/09 17:43:16 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

static	char	*copy_str(char *line, char *str)
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
	(*line) += i - 1;
	return (str);
}
