/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:57:19 by rtakashi          #+#    #+#             */
/*   Updated: 2023/02/07 11:38:07 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ans;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL && s2 == NULL)
		return (ft_strdup(""));
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ans = (char *)ft_calloc(sizeof(char), s1_len + s2_len + 1);
	if (ans == NULL)
		return (NULL);
	ft_strlcpy(ans, s1, s1_len + 1);
	ft_strlcpy(ans + s1_len, s2, s2_len + 1);
	return (ans);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*arr;
// 	int		i;
// 	char	s1[]= "42tokyo";
// 	char	s2[]= "abc!!!";

// 	i = 0;
// 	arr = ft_strjoin(s1, s2);
// 	while (i < 10)
// 		printf("%c\n", arr[i++]);
// 	printf("%s\n", arr);
// 	return (0);
// }
