/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:06:39 by razasharuku       #+#    #+#             */
/*   Updated: 2023/07/25 19:48:37 by sraza            ###   ########.fr       */
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
# include <stdbool.h>
# include"./libft/libft.h"

typedef struct s_word_list
{
	struct s_word_list	*next;
	char				*word;
	int					flag;
}			t_word_list;

typedef struct s_env_list
{
	char				*env_name;
	char				*env_str;
	int					write_flg;
	int					exit_status;
	struct s_env_list	*next;
}						t_env_list;

typedef enum s_flags
{
	command = 1,
	option,
	arguments,
	env,
	pipe_char = 5,
	output,
	append,
	input,
	heredoc,
	meta_char = 10,
	out_file,
	append_file,
	intput_file,
	heredoc_file = 14,
}			t_flags;

//parse_line.c
void					parse_line(char *line);
void					print_words(t_word_list *string);

//parse_line_1.c
t_word_list				*set_flags(t_word_list	*string);
//make_list.c
t_word_list				*make_list(char *line);

//make_list2.c
t_word_list				*ft_newlst(char *content);
int						dquotes_sprt(char *line);
int						squotes_sprt(char *line);
t_word_list				*creat_list(char *line, int i);
t_word_list				*sp_sprt(char **line, t_word_list *string, int i);
//make_list3.c
t_word_list				*find_meta(t_word_list *string);
t_word_list				*split_list(t_word_list *string, char *flag);
int						is_meta(char *str);
//make_list4.c
t_word_list				*argument_flag(t_word_list *string);

//is_something.c

//utils.c
void					*ft_free_line2(char **result);
char					*duplicate(char *content, char *line, unsigned int n);
//split_str.c
char					**split_str(char *str, char *charset);
//get_env.c
t_env_list				*init_minishell(char **envp, t_env_list **env_list_head);
//change_line.c
char					*change_line(char *line, t_env_list *env_list);


#endif