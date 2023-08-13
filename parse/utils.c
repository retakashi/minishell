/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:03:22 by sraza             #+#    #+#             */
/*   Updated: 2023/08/13 16:25:42 by sraza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_free_line2(char **result)
{
	size_t	i;

	i = 0;
	while (result[i] != NULL)
	{
		free(result[i]);
		result[i] = NULL;
		i++;
	}
	free(result);
	result = NULL;
	return (NULL);
}

/*ここの中に完全コピーする関数を作る必要がある
内容はlineをポインタで進めているのでそれをコピーできるようにする。*/
char	*duplicate(char *content, char *line, unsigned int n)
{
	unsigned int	i;
	unsigned int	str_len;

	str_len = ft_strlen(line);
	i = 0;
	while (i < n)
	{
		if (i >= str_len)
			break ;
		else
			content[i] = *line;
		line++;
		i++;
	}
	content[i] = '\0';
	return (content);
}

int	len_of_string(t_word_list *string)
{
	int	i;

	i = 0;
	while (string)
	{
		i++;
		string = string->next;
	}
	return (i);
}

int	count_quotes_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '"')
	{
		i++;
		while (str[i] != '"' && str[i] != '\0')
			i++;
	}
	else if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'' && str[i] != '\0')
			i++;
	}
	if (str[i] != '\0')
		return (i + 1);
	return (i);
}
