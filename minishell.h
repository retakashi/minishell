/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:42:48 by reira             #+#    #+#             */
/*   Updated: 2023/07/15 17:32:11 by reira            ###   ########.fr       */
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
	int					sort_num;
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
void					additionally_write(t_word_list **word_head,
							t_fd *fd_struct);

#endif