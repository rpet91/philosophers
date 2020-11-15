/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 09:09:42 by rpet          #+#    #+#                 */
/*   Updated: 2020/11/15 13:41:53 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stddef.h>
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
	unsigned long		start_time;
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
	unsigned long		eat_time;
	pthread_mutex_t		*fork_one;
	pthread_mutex_t		*fork_two;
	pthread_t			philo_thread;
	t_data				*data;
}						t_philo;

/*
**		Function where the threads are created
*/

int						create_threads(t_philo **philo);

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
**		Time function
*/

unsigned long			get_time(void);

/*
**		Util functions
*/

void					philo_putnb(unsigned long nb);
size_t					philo_strlen(const char *str);
int						philo_error(const char *error);
unsigned long			philo_atoi(const char *str);

#endif
