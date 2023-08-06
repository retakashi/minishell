/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:04:23 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/30 16:51:10 by sraza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	check_sep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i ++;
	}
	return (0);
}

int	count_str(char *str, char *charset)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		while (*str != '\0' && check_sep(*str, charset) == 1)
			str ++;
		if (*str != '\0')
			count++;
		while (*str != '\0' && check_sep(*str, charset) == 0)
			str ++;
	}
	return (count);
}

char	*add_str(char *str, char *charset)
{
	int		i;
	int		add_count;
	char	*add;

	i = 0;
	add_count = 0;
	while (str[add_count] && check_sep(str[add_count], charset) == 0)
		add_count ++;
	add = malloc(sizeof(char) * (add_count + 1));
	while (i < add_count)
	{
		add[i] = str[i];
		i ++;
	}
	add[i] = '\0';
	return (add);
}

char	**split_str(char *str, char *charset)
{
	int		i;
	int		strings_count;
	char	**result;

	i = 0;
	strings_count = count_str(str, charset);
	result = malloc(sizeof(char *) * strings_count + 2);
	if (result == NULL)
		return (0);
	while (*str != '\0')
	{
		while (*str != '\0' && check_sep(*str, charset) == 1)
			str ++;
		if (*str != '\0')
			result[i++] = add_str(str, charset);
		while (*str != '\0' && check_sep(*str, charset) == 0)
			str ++;
	}
	result[i] = NULL;
	return (result);
}
