/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 22:17:56 by rtakashi          #+#    #+#             */
/*   Updated: 2023/02/11 20:07:05 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	dst_cat;

	srclen = ft_strlen(src);
	if (dst == NULL && dstsize == 0)
		return (srclen);
	dstlen = ft_strlen(dst);
	if (dstlen >= dstsize)
		return (srclen + dstsize);
	dst_cat = dstsize - dstlen;
	ft_strlcpy(dst + dstlen, src, dst_cat);
	return (dstlen + srclen);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	size_t	i;
// 	size_t	j;

// 	char dst1[100] = "42tokyo";
// 	char src1[] = "!!";
// 	char dst2[100] = "42tokyo";
// 	char src2[] = "!!";
// 	i = 0;
// 	while (i < 101)
// 	{
// 		printf("original= %lu\n", strlcat(dst1, src1, i));
// 		printf("original= %s\n", dst1);
// 		printf("ft= %lu\n", ft_strlcat(dst2, src2, i));
// 		printf("ft= %s\n", dst2);
// 		j = 0;
// 		if (strncmp(dst1, dst2, i) != 0)
// 		{
// 			printf("No");
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (0);
// }
