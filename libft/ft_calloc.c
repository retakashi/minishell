/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:58:08 by rtakashi          #+#    #+#             */
/*   Updated: 2023/02/07 17:30:24 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*s;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	if (count > SIZE_MAX / size)
		return (NULL);
	s = malloc(count * size);
	if (s == NULL)
		return (NULL);
	ft_bzero(s, count * size);
	return (s);
}

// -fsanitize=address
// int    main (void)
// {
//     long *pMMem;    //for malloc
//     long *pCMem;    //for calloc
//     long *ftMem;    //for ft_calloc

//     pMMem = (long *)malloc (sizeof(long) * 3);
//     pCMem = (long *)calloc (3, sizeof(long));
//     ftMem = (long *)ft_calloc (3,sizeof(long));

//     printf("malloc [0]:%ld, [1]:%ld, [2]:%ld\n", pMMem[0], pMMem[1],
// 		pMMem[2]);
//     printf("calloc [0]:%ld, [1]:%ld, [2]:%ld\n", pCMem[0], pCMem[1],
// 		pCMem[2]);
//     printf("ft_calloc [0]:%ld, [1]:%ld, [2]:%ld\n", ftMem[0], ftMem[1],
// 		ftMem[2]);

//     free(pMMem);
//     free(pCMem);
//     free(ftMem);

//     return(0);
// }
