/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:03:22 by sraza             #+#    #+#             */
/*   Updated: 2023/07/12 15:35:48 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;
	unsigned int	str_len;

	str_len = ft_strlen(src);
	i = 0;
	while (i < n)
	{
		if (i >= str_len)
			dest[i] = '\0';
		else
			dest[i] = src[i];
		i++;
	}
	if (!(i - 1 >= str_len))
		dest[i] = '\0';
	return (dest);
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
