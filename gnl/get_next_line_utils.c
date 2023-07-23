/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:57:57 by rtakashi          #+#    #+#             */
/*   Updated: 2023/06/06 15:37:57 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*ans;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		if (s1 == NULL)
			return (NULL);
		s1[0] = '\0';
	}
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = (ft_strlen(s1));
	s2_len = (ft_strlen(s2));
	ans = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (ans == NULL)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(ans, s1, s1_len + 1);
	ft_strlcpy(ans + s1_len, s2, s2_len + 1);
	free(s1);
	return (ans);
}
