/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:33:25 by rtakashi          #+#    #+#             */
/*   Updated: 2023/01/21 14:41:59 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*casted_s;
	unsigned char	casted_c;
	size_t			i;

	casted_s = (unsigned char *)s;
	casted_c = (unsigned char)c;
	i = 0;
	if (n == 0)
		return (0);
	while (n - i > 0)
	{
		if (casted_s[i] == casted_c)
			return (&casted_s[i]);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// char str[]="42tokyo";
// int str2[]={1,2,3,4,5};
// printf("%s\n", memchr(str, 'y', 5));
// printf("ft= %s\n", ft_memchr(str, 'y', 5));
// printf("%s\n", memchr(str2, 3, 5));
// printf("ft= %s\n", ft_memchr(str2, 3, 5));
// printf("%s\n", memchr(str, 'y', 10));
// printf("ft=%s\n", ft_memchr(str, 'y', 10));
// printf("%s\n", memchr(str, '\0', 10));
// printf("ft=%s\n", ft_memchr(str, '\0', 10));
// printf("%s\n", memchr(NULL, 'y', 0));
// printf("ft=%s\n", ft_memchr(NULL, 'y', 0));
// ↓segmentation fault
// printf("%s\n", memchr(NULL, 'y', 10));
// printf("ft=%s\n", ft_memchr(NULL, 'y', 10));
// return (0);
// }
