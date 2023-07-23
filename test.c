/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:49:05 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/23 20:07:13 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	char	*str;
	size_t	i;

	str = "nnnannn";
	i = 0;
	while (i < 6)
	{
		if (strchr(&str[i], 'n') == NULL)
			printf("hello\n");
		i++;
	}
	return (0);
}
