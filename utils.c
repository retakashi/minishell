/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:03:22 by sraza             #+#    #+#             */
/*   Updated: 2023/07/28 20:52:02 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"execve_cmd.h"
#include"libft/libft.h"
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
