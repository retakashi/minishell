# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reira <reira@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/07 17:05:16 by rtakashi          #+#    #+#              #
#    Updated: 2023/07/30 23:14:03 by reira            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = libft/libft.a
GNL = ../gnl/get_next_line.c ../gnl/get_next_line_utils.c
SRCS = builtin_error.c builtin.c cd_and_pwd.c child_utils.c command.c echo.c env.c error.c execve_cmd_utils.c execve_cmd.c execve_one_cmd.c \
	execve_some_cmds.c exit.c export_nooption.c export_utils.c export.c fork_execve_cmd.c free_exit.c free.c ft_atoll.c \
	get_cmd_argv.c get_env_2darr.c get_env_list.c get_heredoc_file.c get_word_list.c heredoc.c in_output_operation.c minishell_utils.c \
	read_word_list.c unset.c $(GNL) \
	parse_line.c \
	parse_line_1.c \
	is_something.c \
	make_list_1.c \
	make_list_2.c \
	make_list_3.c \
	make_list_4.c \
	utils.c \
	change_line.c \
	split_str.c
OBJS = ${addprefix $(OBJS_DIR)/,$(SRCS:.c=.o)}
OBJS_DIR = objs

RM = rm -f

.DEFAULT_GOAL :=$(NAME)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
${OBJS_DIR}/%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	make clean -C libft
	$(RM) $(OBJS) $(LIBFT) $(GNL)

fclean: clean
	$(RM) $(NAME) $(LIBFT) $(GNL)

re: fclean all

.PHONY: all clean fclean re leaks
