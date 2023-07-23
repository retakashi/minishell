/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:47:56 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/23 22:38:15 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	pwd_cmd(t_word_list **word_list, t_env_list **env_list, int fd)
{
	char	*cwd;

	cwd = get_cwd(NULL, 0);
	ft_putstr_fd(cwd, fd);
	free(cwd);
	return (SUCCESS);
}
