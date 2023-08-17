/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:02:38 by reira             #+#    #+#             */
/*   Updated: 2023/08/17 16:14:57 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test(char **str)
{
    printf("str %c\n",(*str)[2]);
}

int main()
{
    char *str;
    str=malloc(sizeof(char)*6);
    strlcpy(str,"hello",6);
    test(&str);
    return(0);
}