# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rpet <marvin@codam.nl>                       +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/23 12:58:28 by rpet          #+#    #+#                  #
#    Updated: 2020/11/15 14:17:55 by rpet          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_three
CC = gcc
FLAGS = -Wall -Wextra -Werror
ifdef DEBUG
	FLAGS += -g -fsanitize=address
endif
OBJSDIR = objs/
_OBJS = main.o init.o utils.o philo_actions.o philo_loop.o philo_processes.o \
		time.o
OBJS = $(addprefix $(OBJSDIR),$(_OBJS))
INC = philosophers.h

.PHONY: all clean fclean re

all: $(NAME)

$(OBJSDIR)%.o: %.c $(INC)
	@mkdir -p objs
	$(CC) $(FLAGS) -I. -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -pthread -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(OBJSDIR)
	rm -f $(NAME)

re: fclean all
