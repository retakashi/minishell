/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reira <reira@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:44:13 by reira             #+#    #+#             */
/*   Updated: 2023/07/31 23:12:33 by reira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

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

#endif