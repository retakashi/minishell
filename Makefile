# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 10:05:15 by razasharuku       #+#    #+#              #
#    Updated: 2023/07/16 11:59:22 by sraza            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
NAME = $(NAME)
NAME	 =	minishell
CFLAGS	 =	-Wall -Werror -Wextra 

SRCS	=	main.c \
			parse_line.c \
			is_something.c \
			make_list.c \
			make_list_2.c \
			make_list_3.c \
			utils.c \
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