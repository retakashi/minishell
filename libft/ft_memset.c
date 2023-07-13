/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:48:15 by rtakashi          #+#    #+#             */
/*   Updated: 2023/01/16 15:48:02 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*casted_b;
	unsigned char	casted_c;
	size_t			i;

	casted_b = (unsigned char *)b;
	casted_c = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		casted_b[i] = casted_c;
		i++;
	}
	return (b);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char dst1[]="42tokyo";
// 	char dst2[]="42tokyo";

// printf("%s\n", ft_memset(dst1, '!', 3));
// printf("%s\n", ft_memset(dst1, '!', 10));
// printf("%s\n", ft_memset(dst1, NULL, 0));
// printf("%s\n", ft_memset(dst1, NULL, 3));
// printf("%s\n", ft_memset(NULL, '!', 0));
// printf("%s\n", ft_memset(NULL, '!', 3));
// printf("%s\n", ft_memset(NULL, NULL, 3));
// printf("%s\n", ft_memset(NULL, NULL, 0));
// printf("%s\n", memset(dst2, '!', 3));
// printf("%s\n", memset(dst2, '!', 10));
// printf("%s\n", memset(dst2, NULL, 0));
// printf("%s\n", memset(dst2, NULL, 3));
// printf("%s\n", memset(NULL, '!', 0));
// printf("%s\n", memset(NULL, '!', 3));
// printf("%s\n", memset(NULL, NULL, 3));
// printf("%s\n", memset(NULL, NULL, 0));
// 	return (0);
// }
