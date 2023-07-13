/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 22:15:15 by rtakashi          #+#    #+#             */
/*   Updated: 2023/02/06 18:59:08 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count(char const *s, char c);
static size_t	word_len_count(char const *s, size_t i, char c);
static char		**ft_free(char **ans);

char	**ft_split(char const *s, char c)
{
	char	**ans;
	size_t	i;
	size_t	j;

	if (s == NULL)
		return (NULL);
	ans = (char **)ft_calloc(sizeof(char *), word_count(s, c) + 1);
	if (ans == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (j < word_count(s, c))
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			ans[j] = ft_substr(s + i, 0, word_len_count(s, i, c));
			if (ans[j] == NULL)
				return (ft_free(ans));
			j++;
		}
		i += word_len_count(s, i, c);
	}
	return (ans);
}

static size_t	word_count(char const *s, char c)
{
	size_t	word;
	size_t	i;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
			word++;
		while (s[i] != c && s[i] != '\0')
			i++;
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	return (word);
}

static size_t	word_len_count(char const *s, size_t i, char c)
{
	size_t	word_len;

	word_len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		word_len++;
		i++;
	}
	return (word_len);
}

static char	**ft_free(char **ans)
{
	size_t	i;

	i = 0;
	while (ans[i] != NULL)
	{
		free(ans[i]);
		i++;
	}
	free(ans);
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	size_t	i;
// 	size_t	word;
// 	char	**ans;
// 	char	s[]= "aaa42atokyoaahelloaaworlda";
// 	i = 0;
// 	word = word_count(s, 'a');
// 	ans = ft_split(s, 'a');
// 	while (i < word)
// 		printf("%s\n", ans[i++]);
// system("leaks a.out");
// 	return (0);
// }
