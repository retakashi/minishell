/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:49:05 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/14 17:06:47 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_fd
{
	int					in_fd;
	int					out_fd;
	int					pipe_fd[2];
	int					here_fd;
	char *str;
}						t_fd;

t_fd *g_str;

void test(t_fd *fd)
{
	fd->here_fd=0;
	fd->in_fd=0;
	fd->out_fd=0;
	fd->pipe_fd[0]=0;
	fd->pipe_fd[1]=5;
	fd->str=malloc(1);
	g_str=fd;
	// printf("fd p %p\n",&fd);
	// printf("str p %p\n",fd.str);
}

void test_2(t_fd fd)
{
	test(&fd);
}

// __attribute__((destructor))
// void destrucor() {
// 	system("leaks a.out");
// }

int	main(int argc, char **argv, char **envp)
{
	t_fd fd;
	fd.pipe_fd[0]=5;
	test_2(fd);
	printf("pipefd[0] %d\n",g_str->pipe_fd[0]);
	printf("pipefd[1] %d\n",g_str->pipe_fd[1]);	
	system("leaks a.out");
	exit(0);
}
