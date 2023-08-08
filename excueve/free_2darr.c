/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2darr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:33:22 by reira             #+#    #+#             */
/*   Updated: 2023/07/31 20:33:41 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"execute_cmd.h"
#include"libft/libft.h"

void	free_int_2darr(int ***arr, int cnt)
{
	int	i;

	i = 0;
	while (i < cnt)
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	free_char_2darr(char ***arr)
{
	size_t	i;

	i = 0;
	while ((*arr)[i] != NULL)
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
}
