# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pperol <pperol@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 16:23:03 by pperol            #+#    #+#              #
#    Updated: 2022/10/13 15:46:30 by pperol           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = libft/ft_strlen.c \
		libft/ft_memset.c \
		libft/ft_bzero.c \
		libft/ft_calloc.c \
		libft/ft_strlcpy.c \
		libft/ft_split.c \
		libft/ft_strncmp.c \
		libft/ft_strjoin.c \
		libft/ft_putstr_fd.c \
		pipex.c

CC = clang

CFLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=address

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
