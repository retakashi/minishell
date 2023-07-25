/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:42:48 by reira             #+#    #+#             */
/*   Updated: 2023/07/25 23:21:03 by reira            ###   ########.fr       */
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

typedef struct s_fd_list
{
	int					in_fd;
	int					out_fd;
	char				*here_file_name;
	int					pipe_cnt;
	struct s_fd_list	*next;
}						t_fd_list;

typedef struct s_execve_struct
{
	char				**envp;
	char				**argv;
	char				**env_path;
	char				*path;
	char				*cmd_path;
	char				*join_cmd;
	int					i;
}						t_execve_struct;

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

//builtin.c
bool					is_builtin(t_word_list *word_list, int *builtin_flg);
int	execve_builtin(t_word_list *word_list,
					t_env_list **env_list,
					t_fd_list *fd_list,
					int builtin_flg);
//cd.c
int						cd_cmd(t_word_list *word_list, t_env_list **env_list);
//command.c
void	main_command(t_word_list **word_list,
					t_env_list **env_list,
					t_fd_list fd_struct);
void					ft_get_env(char *str, t_env_list *env_list,
							t_env_list **tmp);
void					get_command(t_word_list **head);
//echo.c
int						echo_cmd(t_word_list *word_list, int fd);
//env.c
int						env_cmd(t_env_list **env_list, int fd);
//error.c
int	put_cd_error_update_exit_status(char *str,
									t_env_list **env_head);
int						command_error(char *str, t_env_list **env_head);
int						cd_error(char *str, t_env_list **env_head);
int						env_error(char *str, t_env_list **env_head);
int	put_error_update_exit_status(char *str,
									t_env_list **env_head);
void					exit_error(char *str);
void					put_error_exit(char *str);
//exit.c
void					exit_cmd(t_word_list *word_list);
//export_nooption.c
int						export_nooption(t_env_list **env_list, int fd);
//export.c
void	export_cmd(t_word_list *word_list,
				t_env_list **env_list,
				int fd);
//fork_execve_cmd.c
int	fork_execve_cmd(t_word_list *word_list,
					t_env_list **env_list,
					t_fd_list *fd_list,
					int pipe_cnt);
//free.c
void					free_fd_list(t_fd_list **list);
void					free_word_list(t_word_list **list);
void					free_env_list(t_env_list **list);
//get_env_list.c
size_t					get_name_len(char *str);
void					new_env_node(t_env_list **node, char *envp);
void					get_env_list(char **envp, t_env_list **head);
//get_fd_list.c
void					get_fd_list(t_word_list *word_list, t_fd_list **fd_list,
							int pipe_cnt);
void	new_fd_node(t_fd_list **node,
					int i);
//get_word_list.c
void					get_word_list(t_word_list **head, char *line);
//heredoc.c
int	main_heredoc(t_word_list *word_list,
					t_fd_list **fd_list,
					t_env_list **env_list);
//get_heredoc_file.c
int	get_heredoc_file(t_fd_list **node, char *eof, t_env_list **env_list);
char	*get_file_name(int i);
//in_output_operation.c
int	in_output_operation(t_word_list *word_list,
						t_fd_list **fd_list,
						t_env_list **env_list);
int						find_filename_to_pipe(t_word_list *word_list);
//minishell_utils.c
void					ft_get_env(char *str, t_env_list *env_list,
							t_env_list **tmp);
int						ft_strcmp(char *s1, char *s2);
int						get_fd(char *file_name, int flg);
//pwd.c
void					pwd_cmd(int fd);
//redirecrion.c
int	main_redirection(t_word_list *word_list,
						t_fd_list **fd_struct,
						int red_flg);
//unset.c
void	unset_cmd(t_word_list *word_list,
				t_env_list **env_list);
#endif
