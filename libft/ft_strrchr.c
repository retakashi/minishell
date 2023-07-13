/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:11:45 by rtakashi          #+#    #+#             */
/*   Updated: 2023/01/23 20:35:30 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	strlen;
	size_t	i;

	i = 0;
	str = (char *)s;
	strlen = ft_strlen(str);
	while (i <= strlen)
	{
		if (str[strlen - i] == (char)c)
			return (&str[strlen - i]);
		i++;
	}
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>
// int	main(void)
// {
// 	char str1[]="42tokyot!!";
// 	char str2[]="";
// printf("ft= %s\n", ft_strrchr(str1, 'o'));
// printf("%s\n", strrchr(str1, 'o'));
// printf("ft= %s\n", ft_strrchr(str1, '\0'));
// printf("%s\n", strrchr(str1, '\0'));
// printf("ft= %s\n", ft_strrchr(str2, '2'));
// printf("%s\n", strrchr(str2, '2'));
// printf("ft= %s\n", ft_strrchr(str2, '\0'));
// printf("%s\n", strrchr(str2, '\0'));
// ----------segmentation fault----------
// printf("%s\n", ft_strrchr(NULL, '\0'));
// printf("%s\n", strrchr(NULL, '\0'));
// printf("%s\n", ft_strrchr(NULL, '4'));
// printf("%s\n", strrchr(NULL, '4'));
// 	return (0);
// }
