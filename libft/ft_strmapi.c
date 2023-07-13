/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:50:05 by rtakashi          #+#    #+#             */
/*   Updated: 2023/02/08 17:15:14 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*str;

	if (s == NULL || f == NULL)
		return (NULL);
	str = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = f((unsigned int)i, s[i]);
		i++;
	}
	return (str);
}

// static unsigned int	test(unsigned int i, char str)
// {
// 	return (i);
// }

// #include <stdio.h>

// int	main(void)
// {
// 	unsigned int	i;
// 	char			str;

// 	i = 4294967295;
// 	str = 'a';
// 	printf("i=%u\n", i + 2);
//unsigned int_max=4294967295 (unsigned int)unsigned int_max+1=0
// 	printf("test=%u\n", test(i, str));
// 	return (0);
// }
