# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/13 21:15:30 by jgomez-d          #+#    #+#              #
#    Updated: 2025/09/21 14:59:12 by jgomez-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = philosophers
CFLAGS  = -Wall -Wextra -Werror -g -fsanitize=address,leak
SRC     = dinner.c init.c monitor.c write.c gettersAndSetters.c main.c parsing.c sync_utils.c handlers.c utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) 

fclean: clean
	@rm -f $(NAME) $(CHEKER)

re: fclean all

.PHONY: all clean fclean re