/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:42:48 by reira             #+#    #+#             */
/*   Updated: 2023/07/28 18:30:43 by reira            ###   ########.fr       */
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
# define UPDATE 2
# define CREATE 3
# define READ 0
# define WRITE 1

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

typedef struct s_here_list
{
	int					here_fd;
	char				*here_file_name;
	int					child_num;
	struct s_here_list	*next;
}						t_here_list;

typedef struct s_fd
{
	int					in_fd;
	int					out_fd;
}						t_fd;

typedef struct s_flg
{
	int					builtin_flg;
	int					exit_error_flg;
}						t_flg;
typedef struct s_proccess_data
{
	int					**pipe_2darr;
	char				**env_2darr;
	pid_t				pid;
	int					i;
	int					pipe_cnt;
}						t_proccess_data;

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
	eof_num
}						t_flags;

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

// builtin.c
bool					is_builtin(t_word_list *word_list, int *builtin_flg);
int						execve_builtin(t_word_list *word_list,
							t_env_list **env_list, t_fd fd_struct,
							t_flg flg_struct);
int						main_builtin(t_word_list *word_list,
							t_env_list **env_list, t_here_list *here_list,
							t_flg flg_struct);
// cd_and_pwd.c
int						cd_cmd(t_word_list *word_list, t_env_list **env_list);
int						pwd_cmd(int fd, int *exit_error_flg);
// command.c
void					get_command(t_word_list **head);
// echo.c
void					echo_cmd(t_word_list *word_list, int fd);
// env.c
int						env_cmd(t_env_list **env_list, int fd);
// error.c
int						put_cd_error_update_exit_status(char *str,
							t_env_list **env_head);
void					command_error(char *str);
int						cd_error(char *str, t_env_list **env_head);
int						env_error(char *str, t_env_list **env_head);
int						put_error_update_exit_status(char *str,
							t_env_list **env_head);
void					exit_error(char *str);
void					put_error_exit(char *str);
// execve_cmd_utils.c
char					**extract_path_from_env_2darr(char **env_2darr);
void					get_cmdpath_execve(t_word_list *word_list,
							char **env_2darr);
void					get_pipe_2darr(int ***pipe_2darr, size_t pipe_cnt);
// exit.c
void					exit_cmd(t_word_list *word_list, t_word_list *word_head,
							t_env_list **env_list);
// export_nooption.c
int						export_nooption(t_env_list **env_list, int fd);
// export.c
int						export_cmd(t_word_list *word_list,
							t_env_list **env_list, int fd, int *exit_error_flg);
bool					search_env_name_advance_list(char *str,
							t_env_list **env_list);
// fork_execve_cmd.c
int						fork_execve_cmd(t_word_list *word_list,
							t_env_list **env_list, t_here_list *here_list,
							int pipe_cnt);
// free.c
void					free_here_list(t_here_list **list);
void					free_word_list(t_word_list **list);
void					free_env_list(t_env_list **list);
void					free_word_env_list(t_word_list **word_list,
							t_env_list **env_list);
void					free_all_list(t_word_list **word_list,
							t_env_list **env_list, t_here_list **here_list);
// ft_atoll.c
long long				ft_atoll(char *str, int *error_flg);
// get_cmd_argv.c
char					**get_cmd_argv(t_word_list *word_list);
// get_env_list.c
size_t					get_name_len(char *str);
int						new_env_node(t_env_list **node, char *envp);
int						get_env_list(char **envp, t_env_list **head);
// get_env_2darr.c
char					**get_env_2darr(t_env_list *env_list);
// get_word_list.c
void					get_word_list(t_word_list **head, char *line);
// heredoc.c
int						get_here_list(t_word_list *word_list,
							t_here_list **here_list);
// get_heredoc_file.c
int						get_heredoc_file(t_here_list **node, char *eof);
char					*get_file_name(int i);
// in_output_operation.c
int						in_output_operation(t_word_list *word_list,
							t_here_list *here_list, t_fd *fd_struct,
							int *exit_error_flg);
int						change_exit_error_flg(int *exit_error_flg);
// minishell_utils.c
void					ft_get_env(char *str, t_env_list *env_list,
							t_env_list **tmp);
int						ft_strcmp(char *s1, char *s2);
int						get_fd(char *file_name, int flg);
// proccess.c
void					child_execve_cmd(t_word_list *word_list,
							t_env_list **env_list, t_here_list *here_list,
							t_proccess_data pro_data);
void					parent(t_proccess_data pro_data);
int						in_output_file_dup2(t_fd fd_struct);
// unset.c
void					unset_cmd(t_word_list *word_list,
							t_env_list **env_list);
void					first_execve_cmd(t_word_list *word_list,
							t_env_list **env_list, t_here_list *here_list,
							t_proccess_data pro_data);
void					middle_execve_cmd(t_word_list *word_list,
							t_env_list **env_list, t_here_list *here_list,
							t_proccess_data pro_data);
void					last_execve_cmd(t_word_list *word_list,
							t_env_list **env_list, t_here_list *here_list,
							t_proccess_data pro_data);

#endif
