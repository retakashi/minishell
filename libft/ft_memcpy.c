/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:40:54 by rtakashi          #+#    #+#             */
/*   Updated: 2023/01/16 15:28:29 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*casted_dst;
	unsigned char	*casted_src;
	size_t			i;

	i = 0;
	casted_dst = (unsigned char *)dst;
	casted_src = (unsigned char *)src;
	if (dst == src)
		return (dst);
	while (i < n)
	{
		casted_dst[i] = casted_src[i];
		i++;
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char dst1[]="42tokyo";
	// char src1[]="hello";
	// char dst2[]="42tokyo";
	// char src2[]="hello";
	// printf("%s\n", ft_memcpy(dst1, src1, 5));
	// printf("%s\n", ft_memcpy(dst1, src1, 10));
	// printf("%s\n", ft_memcpy(dst1, NULL, 3));
	// printf("%s\n", ft_memcpy(NULL, src1, 3));
	// printf("%s\n", ft_memcpy(NULL, NULL, 3));
	// printf("%s\n", ft_memcpy(NULL, NULL, 0));
	// printf("%s\n", memcpy(dst2, src2, 5));
	// printf("%s\n", memcpy(dst2, src2, 10));
	// printf("%s\n", memcpy(dst2, NULL, 3));
	// printf("%s\n", memcpy(NULL, src2, 3));
	// printf("%s\n", memcpy(NULL, NULL, 3));
	// printf("%s\n", memcpy(NULL, NULL, 0));
// 	return (0);
// }
