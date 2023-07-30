/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:42:48 by reira             #+#    #+#             */
/*   Updated: 2023/07/30 17:56:15 by rtakashi         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
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
	int					exit_flg;
}						t_flg;

typedef struct s_cmd
{
	char				**path;
	char				**cmd_argv;
	char				*cmd_path;
}						t_cmd;

typedef struct s_p_data
{
	int					**pipe_2darr;
	int					i;
	int					cnt;
}						t_p_data;

typedef struct s_child
{
	t_fd				fd_struct;
	t_flg				flg_struct;
	t_here_list			*tmp;
	t_word_list			*tmp_word;
}						t_child;

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
	in_file,
	eof_num = 14,
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

// builtin_error.c
int						cd_error(char *str);
void					exit_error(char *str);
int	export_error_update_exit_status(char *str,
									t_env_list **env_list);
int	env_error_update_exit_status(char *str,
									t_env_list **env_list);
// builtin.c
bool					is_builtin(t_word_list *word_list, int *builtin_flg);
int						execve_builtin(t_word_list *word_list,
							t_env_list **env_list, t_fd fd_struct,
							t_flg *flg_struct);
int						main_builtin(t_word_list **word_list,
							t_env_list **env_list, t_here_list **here_list,
							t_flg flg_struct);
// cd_and_pwd.c
int						cd_cmd(t_word_list *word_list, t_env_list **env_list);
int						pwd_cmd(int fd, int *exit_flg);
//child_utils.c
void					in_out_file_dup2(t_fd fd_struct,
							t_word_list **word_list, t_env_list **env_list,
							t_here_list **here_list);
void					close_middle_pipe(t_p_data p_data,
							t_word_list **word_list, t_env_list **env_list,
							t_here_list **here_list);
void					close_pipe(t_p_data p_data, t_word_list **word_list,
							t_env_list **env_list, t_here_list **here_list);
void					dup2_middle_pipe(t_p_data p_data,
							t_word_list **word_list, t_env_list **env_list,
							t_here_list **here_list);
void					dup2_close_pipe(t_p_data p_data,
							t_word_list **word_list, t_env_list **env_list,
							t_here_list **here_list);
// command.c
void					get_command(t_word_list **head);
// echo.c
void					echo_cmd(t_word_list *word_list, int fd);
// env.c
int						env_cmd(t_env_list **env_list, int fd);
// error.c
int						put_error(char *str);
int						ft_perror(char *str);
void					command_error(char *str);
char					**perror_change_err_flg(char *err_msg, int *err_flg);
int						update_exit_status(t_env_list **env_list);
//execve.cmd.c
char					*get_cmd_path(char **path, int i, char **env_2darr,
							char **cmd_argv);
char					**extract_path_from_env_2darr(char **env_2darr,
							char **cmd_argv);
void					execve_cmd(char **env_2darr, char **cmd_argv);
//execve_one_cmd.c
void					prepare_execve_cmd(t_word_list **word_list,
							t_env_list **env_list, t_here_list **here_list);
int						execve_one_cmd(t_word_list **word_list,
							t_env_list **env_list, t_here_list **here_list);
//execve_some_cmds.c
void					put_pipe_error_exit(t_p_data p_data,
							t_word_list **word_list, t_env_list **env_list,
							t_here_list **here_list);
void					put_fork_error_exit(t_p_data p_data,
							t_word_list **word_list, t_env_list **env_list,
							t_here_list **here_list);
void					wait_update_status(int cnt, t_word_list **word_list,
							t_env_list **env_list, t_here_list **here_list);
void					search_here_list_child_num(t_here_list *here_list,
							t_here_list **tmp, int i);
void					advance_word_list(t_word_list *word_list,
							t_word_list **tmp, int start);
void					prepare_execve_some_cmds(t_word_list **word_list,
							t_env_list **env_list, t_here_list **here_list,
							int start);
void					child_execve_cmds(t_word_list **word_list,
							t_env_list **env_list, t_here_list **here_list,
							t_p_data p_data);
void					parent_close(t_word_list **word_list,
							t_env_list **env_list, t_here_list **here_list,
							t_p_data p_data);
void					execve_some_cmds(t_word_list **word_list,
							t_env_list **env_list, t_here_list **here_list,
							t_p_data p_data);
// exit.c
void	exit_cmd(t_word_list **word_list,
				t_env_list **env_list);
// export_nooption.c
int						export_nooption(t_env_list **env_list, int fd);
// export_utils.c
void					write_env_exportver(t_env_list *env_list, int fd);
bool	search_env_name_advance_env_list(char *str,
										t_env_list **env_list);
// export.c
int	export_cmd(t_word_list *word_list,
				t_env_list **env_list,
				int fd,
				int *exit_flg);
// fork_execve_cmd.c
int						get_pipe_2darr(int ***pipe_2darr, int pipe_cnt);
int						fork_execve_cmd(t_word_list **word_list,
							t_env_list **env_list, t_here_list **here_list,
							int pipe_cnt);
//free_exit.c
void					free_list_exit(t_word_list **word_list,
							t_env_list **env_list, t_here_list **here_list);
void					perror_free_list_exit(char *str,
							t_word_list **word_list, t_env_list **env_list,
							t_here_list **here_list);
void					free_list_pipe2darr_exit(t_p_data p_data,
							t_word_list **word_list, t_env_list **env_list,
							t_here_list **here_list);
void					free_2darr_exit(char ***arr, char ***arr2);
void					perror_free_2darr_exit(char *err_msg, char ***arr,
							char ***arr2);
// free.c
void					free_word_list(t_word_list **list);
void					free_env_list(t_env_list **list);
void					free_here_list(t_here_list **list);
void					free_all_list(t_word_list **word_list,
							t_env_list **env_list, t_here_list **here_list);
void					free_int_2darr(int ***arr,int cnt);
void					free_char_2darr(char***arr);
// ft_atoll.c
long long				ft_atoll(char *str, int *error_flg);
// get_cmd_argv.c
char					**get_cmd_argv(t_word_list *word_list, int *err_flg);
// get_env_2darr.c
char					**get_env_2darr(t_env_list *env_list, int *err_flg);
// get_env_list.c
size_t					get_name_len(char *str);
int						new_env_node(t_env_list **node, char *envp);
int						get_env_list(char **envp, t_env_list **head);
//get_heredoc_file.c
char					*get_file_name(int i);
int						get_heredoc_file(t_here_list **node, char *eof);
// get_word_list.c
void					get_word_list(t_word_list **head, char *line);
// heredoc.c
int	get_here_list(t_word_list *word_list,
					t_here_list **here_list);
// in_output_operation.c
int						in_output_operation(t_word_list *word_list,
							t_here_list *here_list, t_fd *fd_struct,
							int *exit_flg);
int						change_exit_flg(int *exit_flg);
int						here_file_unlink(t_here_list *here_list, int *exit_flg);
// minishell_utils.c
void					ft_get_env(char *str, t_env_list *env_list,
							t_env_list **tmp);
int						ft_strcmp(char *s1, char *s2);
int						get_fd(char *file_name, int flg);
//read_word_list.c
bool					is_word_list_flag(t_word_list *word_list, int flag);
int						cnt_pipe(t_word_list *word_list);
void					get_here_list_child_num(t_word_list *word_list,
							t_here_list **here_list);
int						read_word_list(t_word_list **word_list,
							t_env_list **env_list, t_here_list **here_list);
void					init_minishell(char **envp, t_env_list **env_list_head,
							t_word_list **word_list_head,
							t_here_list **here_list);
// unset.c
void					get_prev_node(t_env_list **env_list,
							t_word_list *word_list);
bool					search_env_name(t_word_list *word_list,
							t_env_list *env_list);
void					remove_node(t_word_list *remove_word,
							t_env_list **env_list, t_env_list **head);
void					unset_cmd(t_word_list *word_list,
							t_env_list **env_list);

typedef struct s_dollar
{
	int					*d_count;
	int					len;
}						t_dollar;

// parse_line.c
t_word_list				*parse_line(char *line);
void					print_words(t_word_list *string);

// parse_line_1.c
t_word_list				*set_flags(t_word_list *string);
// make_list.c
t_word_list				*make_list(char *line);

// make_list2.c
t_word_list				*ft_newlst(char *content);
int						dquotes_sprt(char *line);
int						squotes_sprt(char *line);
t_word_list				*creat_list(char *line, int i);
t_word_list				*sp_sprt(char **line, t_word_list *string, int i);
// make_list3.c
t_word_list				*find_meta(t_word_list *string);
t_word_list				*split_list(t_word_list *string, char *flag);
int						is_meta(char *str);
// make_list4.c
t_word_list				*argument_flag(t_word_list *string);

// is_something.c

// utils.c
void					*ft_free_line2(char **result);
char					*duplicate(char *content, char *line, unsigned int n);
// split_str.c
char					**split_str(char *str, char *charset);
// change_line.c
char					*change_line(char *line, t_env_list *env_list);

#endif
