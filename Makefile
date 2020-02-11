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

NAME= ft_ls

SRC= check_flag.c \
	ft_ls.c \
	ft_readdir.c \
	get_dir.c \
	get_files.c \
	print.c \
	print_spaces.c \
	recursive.c \
	reverse.c \
	sort.c \
	stockage.c \
	swap_content.c
	 

OBJ= $(SRC:.c=.o)

CC= gcc
CFLAGS= -Wall -Wextra -Werror

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) libft/libft.a $(OBJ) -o $(NAME)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
		make clean -C libft
		rm -f $(OBJ)

.PHONY: fclean
fclean: clean
		make fclean -C libft
		rm -f $(NAME)

re: fclean all
