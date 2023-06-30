# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/03 10:15:08 by wcorrea-          #+#    #+#              #
#    Updated: 2023/06/30 16:28:36 by wcorrea-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/main.c \
		src/environment.c \
		src/input.c \
		src/parse.c \
		src/signals.c \
		src/redirections.c src/heredoc.c \
		src/tokens.c src/tokens_utils.c src/tokens_split.c \
		src/commands_manager.c src/commands_execute.c src/commands_utils.c \
		src/builtins_basic.c src/builtins_complex.c src/builtins_utils.c \
		src/builtins_export_lists.c src/builtins_export_tmp.c \
		src/utils.c src/utils_extra.c

OBJS = ${SRC:.c=.o}

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
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
