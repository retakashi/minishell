/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:42:48 by reira             #+#    #+#             */
/*   Updated: 2023/07/16 01:22:33 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "gnl/get_next_line.h"
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
# define COMMAND_ERROR -2
# define ENV_ERROR -3

typedef struct s_word_list
{
	struct s_word_list	*next;
	char				*word;
	int					flag;
}						t_word_list;

typedef struct s_env_list
{
	char				*env_name;
	char				*env_str;
	int					write_flg;
	bool				shell_variable;
	struct s_env_list	*next;
}						t_env_list;

typedef struct s_fd
{
	int					in_fd;
	int					out_fd;
	int					pipe_fd[2];
	int					here_fd;
}						t_fd;

typedef struct s_execve_args
{
	char				**env_path;
	char				**argv;
}						t_execve_args;

//freeを楽にするためにグローバル変数に先頭のポインタを格納
typedef struct s_shell
{
	t_word_list			*word_head;
	t_env_list			*env_head;
	char				**envp_2d_arr;
	t_execve_args		*execve_args_p;
	t_fd				*fd_struct;
	int					exit_status;

}						t_shell;

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

extern t_shell			*g_shell_struct;

// addtionally_write.c
void	additionally_write(t_word_list **word_head,
						t_fd *fd_struct);
//cd.c
void					cd_cmd(t_word_list **word_list, t_env_list *env_list);
//command.c
void					main_command(t_word_list *word_list,
							t_env_list *env_list);
void					ft_get_env(char *str, t_env_list *env_list,
							t_env_list **tmp);
//echo.c
void					echo_cmd(t_word_list **word_list);
//env.c
void					env_cmd(t_word_list **word_list, t_env_list *env_list);
//error.c
void					perror_exit(char *str, int error_flg);
//exit.c
void					exit_cmd(t_word_list **word_list);
//export.c
void					export_cmd(t_word_list **word_list,
							t_env_list **env_list);
//get_env_list.c
size_t					get_name_len(char *str);
void					new_node(t_env_list **node, char *envp);
void					get_env_list(char **envp, t_env_list **head);
//get_word_list.c
void					get_word_list(t_word_list **head, char **argv);
//heredoc.c
void					create_heredoc(t_word_list **word_head,
							t_fd *fd_struct);
//pwd.c
void					pwd_cmd(t_word_list **word_list, t_env_list *env_list);
//redirection.c
void					main_redirection(t_word_list **word_list,
							t_fd *fd_struct);
//export.nooption.c
int						ft_strcmp(char *s1, char *s2);
void					export_nooption(t_env_list *env_list);
//pwd.c
void					pwd_cmd(t_word_list **word_list, t_env_list *env_list);
//redirecrion.c
void					main_redirection(t_word_list **word_list,
							t_fd *fd_struct);
//unset.c
void					unset_cmd(t_word_list **word_list,
							t_env_list **env_list);

#endif