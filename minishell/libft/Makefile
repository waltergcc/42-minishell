# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anvieira <anvieira@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 01:34:02 by wcorrea-          #+#    #+#              #
#    Updated: 2023/06/22 17:36:20 by anvieira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FT_IS = ft_isprint.c ft_isascii.c ft_isalnum.c ft_isdigit.c \
		ft_isalpha.c ft_isset.c

FT_TO = ft_tolower.c ft_toupper.c ft_atoi.c ft_itoa.c

FT_PUT = ft_putchar.c ft_putstr.c ft_putnbr.c ft_putendl.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

FT_MEM = ft_bzero.c ft_calloc.c ft_memcpy.c ft_memchr.c \
		ft_memcmp.c ft_memset.c ft_memmove.c ft_memalloc.c \
		ft_memccpy.c ft_memdel.c

FT_LST = ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
		ft_lstmap.c ft_lstsize.c ft_lstlast.c

FT_STR = ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c \
		ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
		ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_strtrim.c ft_substr.c ft_strstr.c ft_strncat.c \
		ft_strclr.c ft_strequ.c ft_strncpy.c ft_strcmp.c \
		ft_striter.c ft_strnequ.c ft_strcpy.c ft_strmap.c \
		ft_strnew.c ft_strcat.c ft_strdel.c ft_split2.c

FT_PRINTF = ft_printf.c ft_print_std.c ft_print_hex.c ft_print_unsigned.c \
		ft_print_address.c ft_check_flags.c ft_flags_utils.c ft_precision_print.c

FT_GNL = get_next_line.c get_next_line_utils.c

SRC = ${FT_IS} ${FT_TO} ${FT_PUT} ${FT_MEM} ${FT_LST} ${FT_STR} ${FT_PRINTF} ${FT_GNL}

OBJS = ${SRC:.c=.o}

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -I .

.c.o:
		${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
		ar rcs ${NAME} ${OBJS}

all:	${NAME}

clean:
		${RM} ${OBJS} ${BONUS_OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re