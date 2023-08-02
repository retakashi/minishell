# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reira <reira@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/07 17:05:16 by rtakashi          #+#    #+#              #
#    Updated: 2023/08/03 02:03:23 by reira            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LIBFT = libft/libft.a
SRCS = builtin_error.c builtin.c cd_and_pwd.c dup2_close.c echo.c env.c error.c execve.c execute_one_cmd.c \
	execute_some_cmds_utils.c execute_some_cmds.c execute_some_cmds_error.c exit.c export_nooption.c export_utils.c export.c \
	main_execute_cmd.c free_exit.c free_list.c free_2darr.c ft_atoll.c get_cmd_argv.c get_env_2darr.c get_env_list.c get_heredoc_file.c \
	heredoc.c set_redirection.c minishell_utils.c read_word_list.c unset.c \
	make_list_1.c parse_line_1.c is_something.c make_list_2.c split_str.c \
	change_line_1.c make_list_3.c utils.c change_line_2.c make_list_4.c parse_line.c
OBJS = ${addprefix $(OBJS_DIR)/,$(SRCS:.c=.o)}
OBJS_DIR = objs

RM = rm -f

.DEFAULT_GOAL :=$(NAME)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	echo > ~/.inputrc set echo-control-characters off
${OBJS_DIR}/%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	make clean -C libft
	$(RM) $(OBJS) $(LIBFT) $(GNL)

fclean: clean
	$(RM) $(NAME) $(LIBFT) $(GNL)

re: fclean all

.PHONY: all clean fclean re
