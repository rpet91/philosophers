/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 09:09:42 by rpet          #+#    #+#                 */
/*   Updated: 2020/10/26 19:51:35 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h> //norm
# include <stddef.h>
# include <stdint.h>
# include <pthread.h>

typedef enum	e_status {
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}				t_status;

typedef struct	s_data {
	int					philo_amount;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					eat_amount;
	pthread_mutex_t		mutex;
}				t_data;

typedef struct	s_philo {
	int					philo_num;
	int					left_fork;
	int					right_fork;
	int					eat_amount;
	t_data				*data;
	pthread_t			philo_thread;
}				t_philo;

/*
**		Initialization functions
*/

void		init_mutexes(t_data *data);
void		init_philosophers(t_data *data, t_philo **philosophers);
void		init_data(t_data *data, int argc, char **argv);
void		validate_input(t_data *data, char **argv);

/*
**		Util functions
*/

size_t		philo_strlen(char *str);
void		philo_error(char *error);
int			philo_atoi(char *str);

#endif
