/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:49:05 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/24 02:06:38 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

static int	ft_size(int n)
{
	int	malloc_size;

	malloc_size = 0;
	if (n < 0)
		malloc_size = 1;
	while (n != 0)
	{
		n = n / 10;
		malloc_size++;
		if (n == 0)
			break ;
	}
	return (malloc_size);
}

static void	ft_putnbr(unsigned int n, int i, char *str)
{
	if (n == 0)
		str[0] = '0';
	if (n <= 9 && n >= 0)
		str[i] = n + '0';
	else if (n > 0)
	{
		ft_putnbr(n / 10, --i, str);
		i++;
		str[i] = n % 10 + '0';
		n = n / 10;
	}
}

static unsigned int	ft_abs(int n)
{
	if (n < 0)
		return (n * (-1));
	else
		return (n);
}

char	*ft_itoa(int n)
{
	int		malloc_size;
	char	*itoa;
	int		i;

	malloc_size = ft_size(n);
	if (n == 0)
		malloc_size = 1;
	itoa = malloc(sizeof(char) * (malloc_size + 1));
	if (itoa == NULL)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		itoa[i] = '-';
		i++;
	}
	ft_putnbr(ft_abs(n), malloc_size - 1, itoa);
	*(itoa + malloc_size) = '\0';
	return (itoa);
}

char	*get_file_name(int i)
{
	char	*file_name;
	char	*file_num;

	file_num = ft_itoa(i);
	file_name = ft_strjoin(".heredoc", file_num);
	if (file_name == NULL)
	{
		free(file_num);
		return (NULL);
	}
	free(file_num);
	if (access(file_name, F_OK) < 0)
		return (file_name);
	free(file_name);
	return (get_file_name(i + 1));
}

__attribute__((destructor)) static void destructor()
{
	system("leaks -q a.out");
}

int	main(void)
{
	char	*str;

	str = get_file_name(0);
	printf("str %s\n", str);
	free(str);
	return (0);
}
