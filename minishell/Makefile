# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/03 10:15:08 by wcorrea-          #+#    #+#              #
#    Updated: 2023/06/03 17:27:32 by wcorrea-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/main.c \
		src/environment.c \
		src/clean.c \
		src/signals.c \
		src/tests.c

OBJS = ${SRC:.c=.o}

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g# -fsanitize=thread
INCLUDE = -I include
MAKE = make -C
LIBFT_PATH = libft
LFLAGS = -L ${LIBFT_PATH} -lft -lreadline

.c.o:
		${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
		${MAKE} ${LIBFT_PATH}
		${CC} ${CFLAGS} ${INCLUDE} ${OBJS} ${LFLAGS} -o ${NAME}

all:	${NAME}

clean:
		${MAKE} ${LIBFT_PATH} clean
		${RM} ${OBJS}

fclean: clean
		${MAKE} ${LIBFT_PATH} fclean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re