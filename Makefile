# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rpet <marvin@codam.nl>                       +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/23 12:58:28 by rpet          #+#    #+#                  #
#    Updated: 2020/10/23 13:06:51 by rpet          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
CC = gcc
FLAGS = -Wall -Wextra -Werror
OBJSDIR = objs/
_OBJS = main.o
OBJS = $(addprefix $(OBJSDIR),$(_OBJS))

.PHONY: all clean fclean re

all: $(NAME)

$(OBJSDIR)%.o: %.c
	@mkdir -p objs
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(OBJSDIR)
	rm -f $(NAME)

re: fclean all
