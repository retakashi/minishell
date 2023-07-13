/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:12:54 by rtakashi          #+#    #+#             */
/*   Updated: 2023/02/06 18:50:56 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	head;
	size_t	tail;
	char	*ans;

	head = 0;
	tail = 0;
	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	while (head < s1_len && ft_strchr(set, s1[head]))
		head++;
	while (tail < s1_len && ft_strchr(set, s1[s1_len - tail]))
		tail++;
	if (head == tail && head == s1_len)
		return (ft_strdup(""));
	ans = ft_substr(s1 + head, 0, s1_len - (head + tail) + 1);
	return (ans);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	s1[]="aa42tokyoahelloaaaaa";
// 	char	set[]= "a";
// printf("%s\n", ft_strtrim(s1, set));
// printf("%s\n", ft_strtrim(NULL, set));
// printf("%s\n", ft_strtrim(NULL, NULL));
// printf("%s\n", ft_strtrim(s1, NULL));
// 	return (0);
// }
