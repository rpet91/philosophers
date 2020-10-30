/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 17:01:16 by rpet          #+#    #+#                 */
/*   Updated: 2020/10/26 19:51:34 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <pthread.h>

/*
**
*/

void	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->mutex, NULL) != 0)
		philo_error("Something went wrong while initialising the mutex\n");
}


/*
**		Mallocs a struct for every philosopher
*/

void	init_philosophers(t_data *data, t_philo **philosophers)
{
	int		i;

	i = 0;
	*philosophers = malloc(sizeof(t_philo) * data->philo_amount);
	if (!*philosophers)
		philo_error("Something went wrong while allocating memory\n");
	while (i < data->philo_amount)
	{
		(*philosophers)[i].philo_num = i;
		(*philosophers)[i].left_fork = i;
		(*philosophers)[i].right_fork = (i + 1) % data->philo_amount;
		(*philosophers)[i].eat_amount = 0;
		(*philosophers)[i].data = data;
		i++;
	}
}

/*
**		Checks if the input is valid
*/

void	validate_input(t_data *data, char **argv)
{
	if (data->philo_amount <= 0)
		philo_error("Invalid input for amount of philosophers\n");
	if (data->time_to_die <= 0)
		philo_error("Invalid input for time to die\n");
	if (data->time_to_eat <= 0)
		philo_error("Invalid input for time to eat\n");
	if (data->time_to_sleep <= 0)
		philo_error("Invalid input for time to sleep\n");
	if (data->eat_amount <= 0 && argv[5])
		philo_error("Invalid input for amount to eat\n");
}

/*
**		Saves all the input in a data struct
*/

void	init_data(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		philo_error("Invalid amount of arguments\n");
	data->philo_amount = philo_atoi(argv[1]);
	data->time_to_die = philo_atoi(argv[2]);
	data->time_to_eat = philo_atoi(argv[3]);
	data->time_to_sleep = philo_atoi(argv[4]);
	if (argv[5])
		data->eat_amount = philo_atoi(argv[5]);
	validate_input(data, argv);
}
