/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 17:01:16 by rpet          #+#    #+#                 */
/*   Updated: 2020/11/01 14:11:27 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <pthread.h>

/*
**	Assigns forks for every philosopher
*/

static void		assign_forks(t_data *data, t_philo **philo, int i)
{
	if (i % 2 == 0)
	{
		(*philo)->fork_one = &data->fork_lock[i];
		(*philo)->fork_two = &data->fork_lock[(i + 1) % data->philo_amount];
	}
	else
	{
		(*philo)->fork_one = &data->fork_lock[(i + 1) % data->philo_amount];
		(*philo)->fork_two = &data->fork_lock[i];
	}
}

/*
**	Creates a struct for every philosopher
*/

int				init_philosophers(t_data *data, t_philo **philo)
{
	int		i;

	data->fork_lock = malloc(sizeof(pthread_mutex_t) * data->philo_amount);	
	*philo = malloc(sizeof(t_philo) * data->philo_amount);
	if (!*philo || !data->fork_lock)
		return (philo_error("Something went wrong while allocating memory"));
	i = 0;
	while (i < data->philo_amount)
	{
		(*philo)[i].philo_num = i;
		(*philo)[i].eat_count = 0;
		(*philo)[i].last_time_eaten = get_time();
		(*philo)[i].data = data;
		assign_forks(data, philo, i);
		i++;
	}
	return (0);
}

/*
**	Initialises the mutex locks for writing status and forks
*/

int				init_mutexes(t_data *data)
{
	int		i;

	if (pthread_mutex_init(&data->death_lock, NULL) != 0)
		return (philo_error("An error occurred during the death lock init"));
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (philo_error("An error occurred during the write lock init"));
	i = 0;
	while (i < data->philo_amount)
	{
		if (pthread_mutex_init(&data->fork_lock[i], NULL) != 0)
			return (philo_error("An error occurred during the fork lock init"));
		i++;
	}
	return (0);
}

/*
**	Checks if the given input is valid
*/

static int		validate_input(t_data *data)
{
	if (data->philo_amount <= 0)
		return (philo_error("Invalid input for amount of philosophers"));
	if (data->time_to_die <= 0)
		return (philo_error("Invalid input for time to die"));
	if (data->time_to_eat <= 0)
		return (philo_error("Invalid input for time to eat"));
	if (data->time_to_sleep <= 0)
		return (philo_error("Invalid input for time to sleep"));
	if (data->max_eat_amount <= 0 && data->eat_requirement == true)
		return (philo_error("Invalid input for amount to eat"));
	return (0);
}

/*
**	Saves all the input in a data struct
*/

int				init_data(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (philo_error("Invalid amount of arguments"));
	data->philo_amount = philo_atoi(argv[1]);
	data->time_to_die = philo_atoi(argv[2]);
	data->time_to_eat = philo_atoi(argv[3]);
	data->time_to_sleep = philo_atoi(argv[4]);
	if (argv[5])
	{
		data->max_eat_amount = philo_atoi(argv[5]);
		data->eat_requirement = true;
	}
	else
	{
		data->max_eat_amount = 1;
		data->eat_requirement = false;
	}
	data->start_time = get_time();
	data->status = ALIVE;
	return (validate_input(data));
}
