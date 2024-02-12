# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 21:52:10 by sbzizal           #+#    #+#              #
#    Updated: 2024/02/12 22:03:45 by sbzizal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = mplayer.cpp

EXEC = mplayer

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

re: fclean all

fclean:
	rm -f $(EXEC)

run: all
	./$(EXEC)

.PHONY: all fclean