/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:33:51 by rtakashi          #+#    #+#             */
/*   Updated: 2023/01/23 22:10:39 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	i;

	srclen = ft_strlen(src);
	i = 0;
	while (src[i] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
	{
		dst[i] = '\0';
	}
	return (srclen);
}

// #include <string.h>
// #include<stdio.h>

// int	main(void)
// {
// 	char dst1[]="42tokyo";
// 	char src1[]="!!!";
// 	char dst2[]="42tokyo";
// 	char src2[]="!!!";
// printf("%lu\n", ft_strlcpy(dst1, src1, 5));
// printf("%s\n", dst1);
// printf("%lu\n", ft_strlcpy(dst1, src1, 1));
// printf("%s\n", dst1);
// printf("%lu\n", strlcpy(dst2, src2, 1));
// printf("%s\n", dst2);
// printf("%lu\n", ft_strlcpy(NULL, NULL, 0));
// printf("%lu\n", ft_strlcpy(NULL, NULL, 5));
// printf("%lu\n", ft_strlcpy(dst1, NULL, 0));
// printf("%s\n", dst1);
// printf("%lu\n", ft_strlcpy(NULL, src1, 0));
// printf("%s\n", dst1);
// printf("%lu\n", strlcpy(dst2, src2, 5));
// printf("%s\n", dst2);
// printf("%lu\n", strlcpy(dst2, src2, 10));
// printf("%s\n", dst2);
// printf("%lu\n", strlcpy(NULL, NULL, 0));
// printf("%lu\n", strlcpy(NULL, NULL, 5));
// printf("%lu\n", strlcpy(dst2, NULL, 0));
// printf("%s\n", dst2);
// printf("%lu\n", strlcpy(NULL, src2, 0));
// printf("%s\n", dst2);
// return (0);
// }
