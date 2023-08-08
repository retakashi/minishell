/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:55:52 by rtakashi          #+#    #+#             */
/*   Updated: 2023/08/05 17:13:14 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE -1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*ft_strjoin_gnl(char *s1, char *s2);
char	*get_next_line(int fd, int *flg);
void	handle_signal_gnl(int sig);
int		set_signal_gnl(void);

#endif
