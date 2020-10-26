# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rpet <marvin@codam.nl>                       +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/23 12:58:28 by rpet          #+#    #+#                  #
#    Updated: 2020/10/26 17:04:33 by rpet          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
CC = gcc
FLAGS = -Wall -Wextra -Werror
OBJSDIR = objs/
_OBJS = main.o init.o utils.o
OBJS = $(addprefix $(OBJSDIR),$(_OBJS))
INC = philosophers.h

.PHONY: all clean fclean re

all: $(NAME)

$(OBJSDIR)%.o: %.c
	@mkdir -p objs
	$(CC) $(FLAGS) -I$(INC) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(OBJSDIR)
	rm -f $(NAME)

re: fclean all
