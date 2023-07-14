# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reira <reira@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/07 17:05:16 by rtakashi          #+#    #+#              #
#    Updated: 2023/07/14 15:44:05 by reira            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
LIBFT = libft/libft.a
GNL = ../gnl/get_next_line.c ../gnl/get_next_line_utils.c
SRCS = builtin.c cd.c echo.c env.c error.c exit.c export.c get_env_list.c pwd.c sort_write_envp_list.c unset.c \
	$(GNL)
OBJS = ${addprefix $(OBJS_DIR)/,$(SRCS:.c=.o)}
OBJS_DIR = objs

RM = rm -f


.DEFAULT_GOAL :=$(NAME)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
${OBJS_DIR}/%.o:%.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@
clean:
	make clean -C libft
	$(RM) $(OBJS) $(LIBFT) $(GNL)

fclean: clean
	$(RM) $(NAME) $(LIBFT) $(GNL)

re: fclean all

.PHONY: all clean fclean re
