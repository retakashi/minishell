/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:55:52 by rtakashi          #+#    #+#             */
/*   Updated: 2023/06/09 15:24:31 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*ft_strjoin_gnl(char *s1, char *s2);
char	*get_next_line(int fd, int *flg);

#endif
