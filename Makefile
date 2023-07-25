# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: razasharuku <razasharuku@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 10:05:15 by razasharuku       #+#    #+#              #
#    Updated: 2023/07/24 11:45:44 by razasharuku      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
NAME = $(NAME)
NAME	 =	minishell
CFLAGS	 =	-Wall -Werror -Wextra 

SRCS	=	main.c \
			parse_line.c \
			parse_line_1.c \
			is_something.c \
			make_list_1.c \
			make_list_2.c \
			make_list_3.c \
			make_list_4.c \
			utils.c \
			get_env.c \
			change_line.c \
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