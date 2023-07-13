/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:42:48 by reira             #+#    #+#             */
/*   Updated: 2023/07/13 17:48:14 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define NAME 1
# define STR 0
# define ADD 1
# define UPDATE 0
# define SYNTAX_ERROR -1
# define COMMAND_ERROR -2
# define ENV_ERROR -3

typedef struct s_word_list
{
	struct s_word_list	*next;
	char				*word;
	int					flag;
}						t_word_list;

typedef struct s_fd
{
	int					in_fd;
	int					out_fd;
	int					pipe_fd[2];
	int					here_fd;
}						t_fd;

typedef struct s_envp
{
	char				*envp_name;
	char				*envp_str;
	int					write_flg;
	int					builtin_flg;
	int					sort_num;
	char				**envp_2d_arr;
	t_word_list			*word_head;
	t_fd				*fd_struct;
	struct s_envp		*next;
}						t_envp;

typedef enum e_builtin_no
{
	echo_no,
	cd_no,
	pwd_no,
	export_no,
	unset_no,
	env_no,
	exit_no
}						t_builtin_no;

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
}						t_flags;

extern t_envp			*g_envp_list;

//get_envp_list.c
void					get_write_flg(t_envp **node, char *envp);
size_t					get_len(char *envp, int flg);
void					get_envp_str(t_envp **node, char *envp,
							size_t name_len);
void					new_node(t_envp **node, char *envp);
void					get_envp_list(char **envp);

//sort_write_envp_list.c
int						ft_strcmp(char *s1, char *s2);
void					export_nooption(void);

//error.c
void					perror_free_exit(char *str);

//env.c
void					env_cmd(char **argv);

//export.c
void					export_cmd(char **argv);
#endif