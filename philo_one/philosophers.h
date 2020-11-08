/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 09:09:42 by rpet          #+#    #+#                 */
/*   Updated: 2020/11/07 13:18:06 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h> //norm
# include <stddef.h>
# include <stdint.h>
# include <pthread.h>
# include <stdbool.h>

typedef enum			e_status {
	ALIVE,
	DEAD
}						t_status;

typedef struct			s_data {
	int					philo_amount;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_eat_amount;
	long				start_time;
	bool				eat_requirement;
	t_status			status;
	pthread_t			monitor;
	pthread_mutex_t		death_lock;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		*fork_lock;
}						t_data;

typedef struct			s_philo {
	int					philo_num;
	int					eat_count;
	long				last_time_eaten;
	pthread_mutex_t		*fork_one;
	pthread_mutex_t		*fork_two;
	pthread_t			philo_thread;
	t_data				*data;
}						t_philo;

/*
**		Functions where we go through the actions for every philosopher
*/

void					write_status(t_philo *philo, char *status);
void					philo_status_check(t_philo *philo, char *status);
void					philo_eat(t_philo *philo);
void					philo_sleep(t_philo *philo);
void					operation_time(int operation_time);

/*
**		Initialization functions
*/

int						init_philosophers(t_data *data, t_philo **philo);
int						init_mutexes(t_data *data);
int						init_data(t_data *data, int argc, char **argv);

/*
**		Util functions
*/

long					get_time(void);
void					philo_putnb(long nb);
size_t					philo_strlen(char *str);
int						philo_error(char *error);
int						philo_atoi(char *str);

#endif
