# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/14 18:49:43 by rtakashi          #+#    #+#              #
#    Updated: 2023/07/07 17:00:40 by rtakashi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_isalnum.c ft_itoa.c ft_memset.c ft_split.c ft_strlcat.c ft_strnstr.c ft_toupper.c ft_isalpha.c ft_memchr.c ft_putchar_fd.c \
		ft_strchr.c ft_strlcpy.c ft_strrchr.c ft_atoi.c ft_isascii.c ft_memcmp.c ft_putendl_fd.c ft_strdup.c ft_strlen.c ft_strtrim.c \
		ft_bzero.c ft_isdigit.c ft_memcpy.c ft_putnbr_fd.c ft_striteri.c ft_strmapi.c ft_substr.c ft_calloc.c ft_isprint.c ft_memmove.c \
		ft_putstr_fd.c ft_strjoin.c ft_strncmp.c ft_tolower.c \
		ft_lstclear.c ft_lstlast.c ft_lstsize.c ft_lstadd_back.c ft_lstdelone.c \
		ft_lstmap.c ft_lstadd_front.c ft_lstiter.c ft_lstnew.c \
	
OBJS = $(SRCS:.c=.o)
# BONUS_OBJS = $(BONUS_SRCS:.c=.o)
# ifdef WITH_BONUS
# OBJS += $(BONUS_OBJS)
# endif
AR = ar
ARFLAGS = rcs
RM = rm -f

.DEFAULT_GOAL :=$(NAME)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

clean: 
	$(RM) $(OBJS) 
# $(BONUS_OBJS)


fclean: clean
	$(RM) $(NAME)

re: fclean all

# bonus: 
# 	@make WITH_BONUS=1	

.PHONY: all clean fclean re
