/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipe_2darr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:38:28 by reira             #+#    #+#             */
/*   Updated: 2023/07/27 21:43:11 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_cmd.h"
#include "libft/libft.h"

void	get_pipe_2darr(int ***pipe_2darr, int pipe_cnt)
{
	int i;

	*pipe_2darr = malloc(sizeof(int *) * pipe_cnt);
	if (*pipe_2darr == NULL)
		return ;
	i = 0;
	while (i < pipe_cnt)
	{
		(*pipe_2darr)[i] = malloc(sizeof(int) * 2);
		if ((*pipe_2darr)[i] == NULL)
		{
			while ((*pipe_2darr)[i] != NULL)
				free((*pipe_2darr)[i++]);
			free(*pipe_2darr);
		}
		i++;
	}
}
