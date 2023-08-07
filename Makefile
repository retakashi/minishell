# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 10:05:15 by razasharuku       #+#    #+#              #
#    Updated: 2023/08/07 12:40:14 by razasharuku      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
NAME = $(NAME)
NAME	 =	minishell
CFLAGS	 =	-Wall -Werror -Wextra -fsanitize=address -g

SRCS	=	main.c \
			parse_line_1.c \
			parse_line_2.c \
			check_error.c \
			make_list_1.c \
			make_list_2.c \
			make_list_3.c \
			make_list_4.c \
			utils.c \
			get_env.c \
			change_line_1.c \
			change_line_2.c \
			change_line_3.c \
			split_str.c

OBJS = ${SRCS:%.c=%.o}

all:	$(NAME)

LIBFT		=	./libft/libft.a

$(NAME):	$(OBJS)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(LIBFT) $(SRCS) -o $(NAME) -lreadline

clean:
	$(MAKE) -C ./libft clean
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re