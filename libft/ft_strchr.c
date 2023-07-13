/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:51:08 by rtakashi          #+#    #+#             */
/*   Updated: 2023/02/13 17:44:44 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i++;
	}
	if (c == '\0')
		return (&str[i]);
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char str1[]="42tokyo";
// 	char str2[]="42tokyo";
// 	char str3[]="";
// 	char str4[]="";
// printf("%s\n", ft_strchr(str1, '4'));
// printf("%s\n", strchr(str2, '4'));
// printf("%s\n", ft_strchr(str1, 't'+100));
// printf("%s\n", strchr(str2, 't'+100));
// printf("%s\n", ft_strchr(str3, '2'));
// printf("%s\n", strchr(str4, '2'));
// printf("%s\n", ft_strchr(str3, '\0'));
// printf("%s\n", strchr(str4, '\0'));
// ---------segmentation fault----------
// printf("%s\n", ft_strchr(NULL, '4'));
// printf("%s\n", strchr(NULL, '4'));
// printf("%s\n", ft_strchr(NULL, '\0'));
// printf("%s\n", strchr(NULL, '\0'));
// return (0);
// }
