/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 09:09:42 by rpet          #+#    #+#                 */
/*   Updated: 2020/10/26 13:33:49 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h> //norm
# include <stddef.h>
# include <stdint.h>

typedef enum	e_status {
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}				t_status;

typedef struct	e_philo {
	t_status	status;
	int			left_fork;
	int			right_fork;
	int64_t		eat_amount;
}				t_philo;

typedef struct	e_data {
	int64_t		philo_amount;
	int64_t		time_to_die;
	int64_t		time_to_eat;
	int64_t		time_to_sleep;
	int64_t		eat_amount;
	t_philo		**philo;
}				t_data;

size_t		philo_strlen(char *str);
int			philo_error(char *error);
int64_t		philo_atoi(char *str);
int			init_data(t_data *data, int argc, char **argv);
int			validate_input(t_data *data, char **argv);

#endif
