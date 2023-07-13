/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:14:41 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/07 22:31:01 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

//argv[0]->exit
//argv[1]->status (0-255) 255<num num=num%256

t_envp	*g_envp_list;

void	exit_cmd(char **argv)
{
	if (argv[1] == NULL)
		exit(EXIT_SUCCESS);
	g_envp_list->exit_status = ft_atoi(argv[1]);
	exit(EXIT_SUCCESS);
}
