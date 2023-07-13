/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:47:56 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/07 22:32:04 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

#define PWD_LEN 4
//"PWD="

void	pwd_cmd(void)
{
	char	*pwd;

	pwd = ft_getenvp("PWD=");
	if (pwd == NULL)
		perror("get envp");
	write(1, &pwd[PWD_LEN], ft_strlen(&pwd[PWD_LEN]));
}
