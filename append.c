/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:31:53 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/23 00:25:21 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	read_heredoc(t_fd *fd_struct)
{
	fd_struct->fd = open(".heredoc_file", O_RDONLY);
	if (fd_struct->fd < 0)
		put_error(".heredoc_file", 0);
	if (unlink(".heredoc_file") < 0)
		put_error("unlink", 0);
	if (dup2(fd_struct->fd, STDIN_FILENO) < 0)
		put_error("dup2", 0);
	if (close(fd_struct->fd) < 0)
		put_error("close", 0);
}

void	main_append(t_fd *fd_struct)
{
	if (dup2(fd_struct->fd, STDOUT_FILENO) < 0)
		put_error("dup2", 0);
	if (close(fd_struct->fd) < 0)
		put_error("close", 0);
}
