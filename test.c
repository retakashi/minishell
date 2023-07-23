/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:49:05 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/22 18:21:03 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int main()
{
    int fd;
    int fd2;
    int fd3;
    fd=open("file1",O_RDWR);
    fd2=dup(fd);
     printf("fd %d fd2 %d\n",fd,fd2);
    dup2(fd,fd2);
    printf("fd %d fd2 %d\n",fd,fd2);
    dup2(fd,STDOUT_FILENO);
     printf("fd %d fd2 %d\n",fd,fd2);
    close(fd);
    write(STDOUT_FILENO,"hello\n",7);
    fd3=open("file2",O_RDONLY);
    printf("fd3 %d\n",fd3);
    printf("hello\n");
    return(0);
}
