/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:49:05 by rtakashi          #+#    #+#             */
/*   Updated: 2023/07/13 19:54:17 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
char *test()
{
	char *str;
	str=malloc(1);
	return(str);
}

__attribute__((destructor))
void destrucor() {
	system("leaks a.out");
}

int	main(int argc, char **argv, char **envp)
{
	
	int i = 0;
	char *str;
		str = test();
	system("leaks a.out");
	exit(0);
}

__attribute__((destructor))
void destrucor() {
	system("leaks a.out");
}
