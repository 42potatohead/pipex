# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zabu-bak <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 11:05:52 by rchallie          #+#    #+#              #
#    Updated: 2025/01/29 18:44:38 by zabu-bak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
       			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
       			ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
      			ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
      			ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
      			ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
      			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
				ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
				ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
OBJS			= $(SRCS:.c=.o)

PRINTF_SRC		= $(addprefix printf/, ft_printf.c ft_print.c ft_numbers.c)

OBJS			= $(SRCS:.c=.o)
PRINTF_OBJS		= $(PRINTF_SRC:.c=.o)

CC				= cc
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror -g

NAME			= libft.a

all:			$(NAME)

$(NAME):		$(OBJS) $(PRINTF_OBJS)
				ar rcs $(NAME) $(OBJS) $(PRINTF_OBJS)

%.o: %.c
				$(CC) $(CFLAGS) -c $< -o $@
clean:
				$(RM) $(OBJS) $(PRINTF_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
