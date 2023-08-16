# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/07 17:05:16 by rtakashi          #+#    #+#              #
#    Updated: 2023/08/15 19:18:24 by razasharuku      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
GNL_DIR = gnl
PARSE_DIR = parse
SIGNAL_DIR = signal
EXECUTE_DIR = execute
PARSE_SRCS = change_line_1.c change_line_2.c  change_line_3.c make_list_1.c make_list_2.c make_list_3.c make_list_4.c \
	parse_line_1.c parse_line_2.c parse_line_3.c split_str.c utils.c check_error.c check_error_2.c
SIGNAL_SRCS = signal.c
EXECUTE_SRCS = builtin_error.c builtin.c cd_and_pwd.c dup2_close.c echo.c env.c error.c execve.c execute_one_cmd.c \
	execute_some_cmds_utils.c execute_some_cmds.c exit.c export_noargs.c export_utils.c export.c \
	main_execute_cmd.c free_exit.c free_list.c free_2darr.c ft_atoll.c get_cmd_argv.c get_env_2darr.c get_env_list.c get_heredoc_file.c \
	heredoc.c set_redirection.c execute_utils.c read_word_list.c unset.c
GNL_SRCS = get_next_line.c get_next_line_utils.c
SRCS = minishell.c
OBJS_DIR = objs
EXECUTE_OBJS = ${addprefix $(OBJS_DIR)/, $(EXECUTE_SRCS:.c=.o)}
EXECUTE_OBJS +=	${addprefix $(OBJS_DIR)/, $(GNL_SRCS:.c=.o)}
OBJS =	${addprefix $(OBJS_DIR)/, $(PARSE_SRCS:.c=.o)} ${addprefix $(OBJS_DIR)/, $(SIGNAL_SRCS:.c=.o)} $(EXECUTE_OBJS) ${addprefix $(OBJS_DIR)/, $(SRCS:.c=.o)}
RL_DIR = $(shell brew --prefix readline)
$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)
$(OBJS_DIR)/%.o: $(PARSE_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I /opt/homebrew/opt/readline/include -c $< -o $@
$(OBJS_DIR)/%.o: $(SIGNAL_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I /opt/homebrew/opt/readline/include -c $< -o $@
$(OBJS_DIR)/%.o: $(EXECUTE_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I /opt/homebrew/opt/readline/include -c $< -o $@
$(OBJS_DIR)/%.o: $(GNL_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I /opt/homebrew/opt/readline/include -c $< -o $@
$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I /opt/homebrew/opt/readline/include -c $< -o $@

RM = rm -f
.DEFAULT_GOAL :=$(NAME)
all: $(NAME)
$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) -lreadline -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include/readline -o $(NAME) $(OBJS) $(LIBFT)
	echo > ~/.inputrc set echo-control-characters off

clean:
	make clean -C libft
	$(RM) $(OBJS) $(LIBFT)

fclean: clean
	$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
