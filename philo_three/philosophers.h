/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 09:09:42 by rpet          #+#    #+#                 */
/*   Updated: 2020/11/09 17:12:01 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stddef.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h> //

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
	sem_t				*death_lock;
	sem_t				*write_lock;
	sem_t				*fork_lock;
}						t_data;

typedef struct			s_philo {
	int					philo_num;
	int					eat_count;
	unsigned long		eat_time;
	t_data				*data;
}						t_philo;

/*
**		Function where the threads are created
*/

void					create_forks(t_data *data);

/*
**		Functions where we go through the actions for every philosopher
*/

void					write_status(t_philo *philo, char *status);
void					philo_eat(t_philo *philo);
void					philo_sleep(t_philo *philo);
void					operation_time(int operation_time);

/*
**		Initialization functions
*/

void					init_philosophers(t_data *data, t_philo *philo);
void					init_mutexes(t_data *data);
void					init_data(t_data *data, int argc, char **argv);

/*
**		Util functions
*/

unsigned long			get_time(void);
void					philo_putnb(unsigned long nb);
size_t					philo_strlen(char *str);
void					philo_error(char *error);
unsigned long			philo_atoi(char *str);

#endif
