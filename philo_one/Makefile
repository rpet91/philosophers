# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rpet <marvin@codam.nl>                       +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/23 12:58:28 by rpet          #+#    #+#                  #
#    Updated: 2020/10/31 10:45:01 by rpet          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
CC = gcc
FLAGS = -Wall -Wextra -Werror
OBJSDIR = objs/
_OBJS = main.o init.o utils.o philo_actions.o
OBJS = $(addprefix $(OBJSDIR),$(_OBJS))
INC = philosophers.h

.PHONY: all clean fclean re

all: $(NAME)

$(OBJSDIR)%.o: %.c $(INC)
	@mkdir -p objs
	$(CC) $(FLAGS) -I. -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -pthread -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(OBJSDIR)
	rm -f $(NAME)

re: fclean all
