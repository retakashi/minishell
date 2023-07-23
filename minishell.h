/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:42:48 by reira             #+#    #+#             */
/*   Updated: 2023/07/24 00:26:58 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE -1
# define ADD 1
# define UPDATE 0
# define COMMAND_ERROR -1
# define EXIT_ERROR -2
# define NO_ERRNO -3
# define CD_ERROR -4
# define EXPORT_ERROR -5
# define SAVE_STDIN 15
# define SAVE_STDOUT 16

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
	int					exit_status;
	struct s_env_list	*next;
}						t_env_list;

typedef struct s_here
{
	int					here_fd;
	char				*here_file_name;
	struct s_here		*next;
}						t_here;
typedef struct s_fd
{
	int					in_fd;
	int					out_fd;
	t_here				*here_list_head;
}						t_fd;

typedef struct s_execve_args
{
	char				**env_path;
	char				**argv;
}						t_execve_args;

typedef enum e_flags
{
	command,
	option,
	arguments,
	env,
	pipe_char,
	output,
	append,
	input,
	heredoc,
	meta_char,
	output_file,
	input_file,
	append_file,
	heredoc_file
}						t_flags;

// append.c
void					main_append(t_fd *fd_struct);
//cd.c
void					cd_cmd(t_word_list **word_list, t_env_list *env_list);
//command.c
void	main_command(t_word_list **word_list,
					t_env_list **env_list,
					t_fd fd_struct);
void					ft_get_env(char *str, t_env_list *env_list,
							t_env_list **tmp);
void					get_command(t_word_list **head);
//echo.c
void					echo_cmd(t_word_list **word_list, int fd);
//env.c
void					env_cmd(t_word_list **word_list, t_env_list *env_list);
//error.c
int						put_error(char *str, int err_flg,
							t_env_list **env_head);
void					put_error_exit(char *str, int flg);
//exit.c
void					exit_cmd(t_word_list **word_list);
//export.c
void	export_cmd(t_word_list **word_list,
				t_env_list **env_list);
bool	cmp_env_name_advance_list(char *str,
								t_env_list **env_list);
//free.c
void					free_word_list(t_word_list **list);
void					free_env_list(t_env_list **list);
//get_env_list.c
size_t					get_name_len(char *str);
void					new_node(t_env_list **node, char *envp);
void					get_env_list(char **envp, t_env_list **head);
//get_word_list.c
void					get_word_list(t_word_list **head, char *line);
//heredoc.c
int						main_heredoc(t_word_list *word_list, t_fd *fd_struct);
//input_output_operation.c
int	input_output_operation(t_word_list *word_list,
							t_fd **fd_list,
							int red_flg);
bool					is_word_list_flags(t_word_list *word_list, int flags);
//minishell_utils.c
void					ft_get_env(char *str, t_env_list *env_list,
							t_env_list **tmp);
int						ft_strcmp(char *s1, char *s2);
int						get_fd(char *file_name, int flg);
//export.nooption.c
int						ft_strcmp(char *s1, char *s2);
void					init_write_flg(t_env_list **env_list);
void					export_nooption(t_env_list *env_list);
//pwd.c
void					pwd_cmd(t_word_list **word_list, t_env_list *env_list);
//redirecrion.c
int	main_redirection(t_word_list *word_list,
						t_fd **fd_struct,
						int red_flg);
//unset.c
void	unset_cmd(t_word_list **word_list,
				t_env_list **env_list);
t_word_list				*parse_line(char *line);

#endif
