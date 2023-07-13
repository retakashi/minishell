/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:57:12 by rtakashi          #+#    #+#             */
/*   Updated: 2023/02/11 14:14:52 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*casted_dst;
	unsigned char	*casted_src;

	casted_dst = (unsigned char *)dst;
	casted_src = (unsigned char *)src;
	if (dst == src)
		return (dst);
	if (dst < src)
		ft_memcpy(casted_dst, casted_src, len);
	else
	{
		while (len > 0)
		{
			casted_dst[len - 1] = casted_src[len - 1];
			len--;
		}
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char dst1[]="42tokyo";
// 	char src1[]="hello";
// 	char dst2[]="42tokyo";
// 	char src2[]="hello";

// printf("%s\n", ft_memmove(dst1, src1, 3));
// printf("%s\n", ft_memmove(dst1, src1, 10));
// printf("%s\n", ft_memmove(dst1, NULL, 0));
// printf("%s\n", ft_memmove(dst1, NULL, 3));
// printf("%s\n", ft_memmove(NULL, src1, 0));
// printf("%s\n", ft_memmove(NULL, src1, 3));
// printf("%s\n", ft_memmove(NULL, NULL, 3));
// printf("%s\n", ft_memmove(NULL, NULL, 0));
// printf("%s\n", memmove(dst2, src2, 3));
// printf("%s\n", memmove(dst2, src2, 10));
// printf("%s\n", memmove(dst2, NULL, 0));
// printf("%s\n", memmove(dst2, NULL, 3));
// printf("%s\n", memmove(NULL, src2, 0));
// printf("%s\n", memmove(NULL, src2, 3));
// printf("%s\n", memmove(NULL, NULL, 3));
// printf("%s\n", memmove(NULL, NULL, 0));
// 	return (0);
// }
