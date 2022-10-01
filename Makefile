# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pperol <pperol@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 16:23:03 by pperol            #+#    #+#              #
#    Updated: 2022/10/01 10:46:50 by pperol           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 	parsing/ft_parsing_c \
		libft/ft_split.c \
		libft/ft_strdup.c \
		libft/ft_strncmp.c \
		libft/ft_strjoin.c \
		pipex.c

CC = clang

CFLAGS =  -g3 #-fsanitize=address
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
