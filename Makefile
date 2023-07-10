# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sraza <sraza@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 10:05:15 by razasharuku       #+#    #+#              #
#    Updated: 2023/07/10 17:22:41 by sraza            ###   ########.fr        #
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
			utils.c \
			split_words.c 

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