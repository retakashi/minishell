/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:06:39 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/12 15:41:02 by razasharuku      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include"./libft/libft.h"

typedef struct s_word_list
{
	struct s_word_list	*next;
	char				*word;
	int					flag;
}			t_word_list;

typedef enum e_flags
{
	command,
	option,
	arguments,
	env,
	pipe_char,
	great,
	great_great,
	less,
	less_less,
	meta_char,
}			t_flags;

//parse_line.c
void					parse_line(char *line);
//make_list.c
t_word_list				*ft_newlst(char *content);
t_word_list				*make_list(char *line);
//split_words.c

//is_something.c

//utils.c
void					*ft_free_line2(char **result);
char					*ft_strncpy(char *dest, char *src, unsigned int n);
char					*duplicate(char *content, char *line, unsigned int n);

#endif