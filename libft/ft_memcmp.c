/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:57:46 by rtakashi          #+#    #+#             */
/*   Updated: 2023/01/21 14:32:28 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*casted_s1;
	unsigned char	*casted_s2;
	size_t			i;

	casted_s1 = (unsigned char *)s1;
	casted_s2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (casted_s1[i] != casted_s2[i])
			return (casted_s1[i] - casted_s2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// char str1[]="42tokyo";
// char str2[]="42to";
// int str3[]={1,2,3,4,5};
// int str4[]={1,2,3};
// printf("%d\n", memcmp(str1, str2, 5));
// printf("ft=%d\n", ft_memcmp(str1, str2, 5));
// printf("%d\n", memcmp(str1, str2, 3));
// printf("ft=%d\n", ft_memcmp(str1, str2, 3));
// printf("%d\n", memcmp(str1, str2, 0));
// printf("ft=%d\n", ft_memcmp(str1, str2, 0));
// printf("%d\n", memcmp(NULL, NULL, 0));
// printf("ft=%d\n", ft_memcmp(NULL, NULL, 0));
// printf("%d\n", memcmp(str3, str4, sizeof(str3)));
// printf("ft=%d\n", ft_memcmp(str3, str4, sizeof(str3)));
// ↓segmentation fault
// printf("%d\n", memcmp(NULL, str2, 5));
// printf("ft=%d\n", ft_memcmp(NULL, str2, 5));
// printf("%d\n", memcmp(str1, NULL, 5));
// printf("ft=%d\n", ft_memcmp(str1, NULL, 5));
// 	return (0);
// }
