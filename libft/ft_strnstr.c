/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:43:49 by rtakashi          #+#    #+#             */
/*   Updated: 2023/02/07 18:52:37 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (haystack[i] != '\0')
	{
		j = 0;
		while (i + j < len && haystack[i + j] == needle[j]
			&& haystack[i + j] != '\0')
		{
			j++;
		}
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// char haystack[]="";
// char needle[]="42tokyo";
// printf("%s\n", strnstr(haystack, needle, 16));
// printf("ft=%s\n", ft_strnstr(haystack, needle, 16));
// printf("%s\n", strnstr(haystack, needle, 15));
// printf("ft=%s\n", ft_strnstr(haystack, needle, 15));
// printf("%s\n", strnstr(haystack, needle, 10));
// printf("ft=%s\n", ft_strnstr(haystack, needle, 10));
// printf("----- NULL -----\n");
// printf("%s\n", strnstr(haystack, needle, 0));
// printf("ft=%s\n", ft_strnstr(haystack, needle, 0));
// printf("6=%s\n", strnstr(haystack, needle, 6));
// printf("ft=%s\n", ft_strnstr(haystack, needle, 6));
// printf("7=%s\n", strnstr(haystack, needle, 7));
// printf("ft=%s\n", ft_strnstr(haystack, needle, 7));
// printf("%s\n", strnstr(haystack, needle, 5));
// printf("ft=%s\n", ft_strnstr(haystack, needle, 5));
// printf("%s\n", strnstr(haystack, needle, 3));
// printf("ft=%s\n", ft_strnstr(haystack, needle, 3));
// printf("%s\n", strnstr(haystack, needle, 2));
// printf("ft=%s\n", ft_strnstr(haystack, needle, 2));
// printf("%s\n", strnstr(haystack, needle, 1));
// printf("ft=%s\n", ft_strnstr(haystack, needle, 1));
// printf("%s\n", strnstr(NULL, needle, 0));
// printf("ft=%s\n", ft_strnstr(NULL, needle, 0));
// printf("----- segmentation fault -----\n");
// printf("%s\n", strnstr(NULL, NULL, 0));
// printf("ft=%s\n", ft_strnstr(NULL, NULL, 0));
// printf("%s\n", strnstr(haystack, NULL, 0));
// printf("ft=%s\n", ft_strnstr(haystack, NULL, 0));
// printf("%s\n", strnstr(haystack, NULL, 2));
// printf("ft=%s\n", ft_strnstr(haystack, NULL, 2));
// printf("%s\n", strnstr(NULL, needle, 3));
// printf("ft=%s\n", ft_strnstr(NULL, needle, 3));
// return (0);
// }
