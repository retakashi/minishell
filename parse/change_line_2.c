/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_line_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:45:51 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/11 21:32:53 by sraza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

static	int	count_env_mark(char *line)
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

static	char	*count_d_str(char **str)
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
	if (i == 1)
		(*str) += i;
	else
		(*str) += i - 1;
	line[i] = '\0';
	return (line);
}

static	char	**give_d_hatena(char **result, char *exit_status,
								char *d_hatena)
{
	int		i;
	int		j;
	size_t	len_status;

	i = 0;
	len_status = ft_strlen(exit_status);
	while (result[i])
	{
		j = 0;
		while (result[i][j])
		{
			if (result[i][j] != d_hatena[j])
				break ;
			if (j == 1 && result[i][j + 1] == '\0')
			{
				free(result[i]);
				result[i] = malloc(sizeof (char) * (len_status + 1));
				result[i] = duplicate(result[i], exit_status, len_status);
				return (result);
			}
			j++;
		}
		i++;
	}
	return (result);
}

char	**make_strlist(char *line, t_env_list *env_list)
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
	max_str = give_d_hatena(max_str, env_list->env_value, "$?");
	return (max_str);
}
