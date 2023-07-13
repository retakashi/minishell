/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:47:56 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/13 18:05:34 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	pwd_cmd(void)
{
	t_envp	*node;

	node = NULL;
	ft_getenvp("PWD", &node);
	if (node == NULL || node->envp_str)
		perror_free_2d_arr_exit("pwd", NULL, NULL, NULL);
	write(1, node->envp_str, ft_strlen(node->envp_str));
	write(1, "\n", 1);
}
