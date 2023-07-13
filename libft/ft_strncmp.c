/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:40:53 by rtakashi          #+#    #+#             */
/*   Updated: 2023/02/07 18:26:50 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	casted_s1;
	unsigned char	casted_s2;
	size_t			i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
		{
			casted_s1 = (unsigned char)s1[i];
			casted_s2 = (unsigned char)s2[i];
			return (casted_s1 - casted_s2);
		}
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// char str1[]="42";
// char str2[]="42tokyo";
// char str3[]="";
// char str4[]="";
// printf("%d\n", strncmp(str1, str2, 0));
// printf("ft=%d\n", ft_strncmp(str1, str2, 0));
// printf("%d\n", strncmp(str1, str2, 1000000));
// printf("ft=%d\n", ft_strncmp(str1, str2, 1000000));
// printf("%d\n", strncmp(str1, str2, 10));
// printf("ft=%d\n", ft_strncmp(str1, str2, 10));
// printf("%d\n", strncmp(NULL, NULL, 0));
// printf("ft=%d\n", ft_strncmp(NULL, NULL, 0));
// printf("%d\n", strncmp(str1, str2, 20));
// printf("ft=%d\n", ft_strncmp(str1, str2, 20));
// printf("ft=%d\n", ft_strncmp(str3, str4, 0));
// printf("%d\n", strncmp(str3, str4, 0));
// ↓segmentation fault
// printf("ft=%d\n", ft_strncmp(str3, str4, 3));
// printf("%d\n", strncmp(str3, str4, 3));
// printf("ft=%d\n", ft_strncmp(str1, NULL, 3));
// printf("%d\n", strncmp(str1, NULL, 3));
// printf("ft=%d\n", ft_strncmp(NULL, str1, 3));
// printf("%d\n", strncmp(NULL, str1, 3));
// return (0);
// }
