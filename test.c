/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:49:05 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/25 00:13:56 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q a.out");
// }

int	main(int argc,char **argv)
{
	if(argc==0||argv==NULL)
	return(0);
	char *str;
	char *args[3]={"wc","-l"};
	str=strdup("/bin/wc");
	char **envp=NULL;
	if(execve(str,args,envp)<0)
	perror(NULL);
	exit(0);
}
