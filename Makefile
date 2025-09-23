# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/13 21:15:30 by jgomez-d          #+#    #+#              #
#    Updated: 2025/09/23 19:26:26 by jgomez-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = philosophers
CFLAGS  = -Wall -Wextra -Werror -O3 -g3 #-fsanitize=thread
SRC     = dinner.c init.c monitor.c write.c gettersAndSetters.c main.c parsing.c handlers.c utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) 

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re