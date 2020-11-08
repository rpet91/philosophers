# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rpet <marvin@codam.nl>                       +#+                      #
#                                                    +#+                       #
#    Created: 2020/10/23 12:58:28 by rpet          #+#    #+#                  #
#    Updated: 2020/11/07 14:18:20 by rpet          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
CC = gcc
FLAGS = -Wall -Wextra -Werror
ifdef DEBUG
	FLAGS += -g -fsanitize=address
endif
OBJSDIR = objs/
_OBJS = main.o init.o utils.o philo_actions.o
SRCS = main.c init.c utils.c philo_actions.c
OBJS = $(addprefix $(OBJSDIR),$(_OBJS))
INC = philosophers.h

.PHONY: all clean fclean re

all: $(NAME)

$(OBJSDIR)%.o: %.c $(INC)
	@mkdir -p objs
	$(CC) $(FLAGS) -I. -c $< -o $@

#$(NAME):
#	$(CC) $(SRCS) $(FLAGS) -o $(NAME)
$(NAME): $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -pthread -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(OBJSDIR)
	rm -f $(NAME)

re: fclean all
