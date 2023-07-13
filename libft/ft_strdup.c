/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:09:38 by rtakashi          #+#    #+#             */
/*   Updated: 2023/02/01 21:35:41 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	str_len;

	str_len = ft_strlen(s1) + 1;
	str = (char *)ft_calloc(sizeof(char), str_len);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, str_len);
	return (str);
}

// int	main(void)
// {
// 	char	*s1;
// 	char	*s2;

// 	char src[]="42tokyo";
// 	s1 = strdup(src);
// 	s2 = ft_strdup(src);
// 	printf("strdup= %s\n", s1);
// 	printf("ft_strdup= %s\n", s2);
// 	return (0);
// }
