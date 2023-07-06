/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:06:39 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/06 13:47:52 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdio.h>
# include <stdarg.h>
# include"./libft/libft.h"

typedef struct s_wrod_desc
{
	char	*word;
	int		flags;
}			t_word_desc;
typedef struct s_wrod_list
{
	struct word_list	*next;
	t_word_desc			*word;
}			t_wrod_list;


void					parse_line(const char *line);


#endif