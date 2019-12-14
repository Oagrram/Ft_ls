# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aymhabib <aymhabib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/16 02:00:08 by aymhabib          #+#    #+#              #
#    Updated: 2019/12/12 23:39:37 by oagrram          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

LIB = libft.a

SRC = *.c

LIBSRC = libft/*.c

INCLDS = ls.h

LIBINCLDS = libft/libft.h

FLAG = -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIB)
		gcc $(FLAG) $(SRC) $(LIB) -o $(NAME)

$(LIB):
		gcc $(FLAG) -c $(LIBSRC) -I $(LIBINCLDS)
		ar rc $(LIB) *.o
clean:
		/bin/rm -f *.o
		/bin/rm -f .DS_Store

fclean: clean
		/bin/rm -f $(NAME)
		/bin/rm -f $(LIB)

re: fclean all
