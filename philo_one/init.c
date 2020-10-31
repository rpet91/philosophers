/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 17:01:16 by rpet          #+#    #+#                 */
/*   Updated: 2020/10/31 14:04:55 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <pthread.h>

/*
**		Initialises the mutexes
*/

int		init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (philo_error("Something went wrong while write mutex init"));
	return (0);
}

/*
**		Mallocs a struct for every philosopher
*/

int		init_philosophers(t_data *data, t_philo **philo)
{
	int		i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * data->philo_amount);
	if (!*philo)
		return (philo_error("Something went wrong while allocating memory"));
	while (i < data->philo_amount)
	{
		(*philo)[i].philo_num = i;
		(*philo)[i].left_fork = i;
		(*philo)[i].right_fork = (i + 1) % data->philo_amount;
		(*philo)[i].eat_count = 0;
		(*philo)[i].data = data;
		i++;
	}
	return (0);
}

/*
**		Checks if the input is valid
*/

int		validate_input(t_data *data)
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
**		Saves all the input in a data struct
*/

int		init_data(t_data *data, int argc, char **argv)
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
		data->eat_requirement = false;
	data->start_time = get_time();
	data->status = ALIVE;
	return (validate_input(data));
}
