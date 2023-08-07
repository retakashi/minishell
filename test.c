/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:49:23 by razasharuku       #+#    #+#             */
/*   Updated: 2023/08/06 20:04:29 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	len1 = 0;
	len2 = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL && s2 != NULL)
		len2 = strlen(s2);
	else if (s1 != NULL && s2 == NULL)
		len1 = strlen(s1);
	else
	{
		len1 = strlen(s1);
		len2 = strlen(s2);
	}
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (str == NULL)
		return (NULL);
	memcpy(str, s1, len1);
	memcpy(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	return (str);
}

char	*joint_array(char **result)
{
	int		i;
	char	*line;
	char	*new_line;

	i = 0;
	line = NULL;
	while (result[i] != NULL)
	{
		new_line = line;
		line = ft_strjoin(line, result[i]);
		free(new_line);
		i++;
	}
	return (line);
}

int main (int argc, char **argv)
{
    char *line;

    if (argc == 1)
        return (0);
    line = joint_array(argv);

    printf("line = %s\n", line);
    exit (0);

}

// __attribute__((destructor))
// static void destructor()
// {
// 	system("leaks -q a.out");
// }