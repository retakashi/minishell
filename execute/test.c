/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:02:38 by reira             #+#    #+#             */
/*   Updated: 2023/08/18 02:06:46 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*get_exname(char *line)
{
	char	*ans;
	size_t	i;

	i = 0;
	while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t'
		&& line[i] != '$')
		i++;
	ans = malloc(sizeof(char) * (i + 1));
	if (ans == NULL)
	{
		perror("failed to get exname");
		return (NULL);
	}
	strlcpy(ans, line, i + 1);
	return (ans);
}

void	test(char **str)
{
	int		i;
	char	*ans;

	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '$')
			ans = get_exname(*str + i + 1);
		printf("ans %s\n", ans);
		i++;
	}
}

int	main(void)
{
	char	*str;

	str = malloc(sizeof(char) * 100);
	strlcpy(str, "he$llo$aaa", strlen("he$llo$aaa"));
	test(&str);
	return (0);
}
