/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/23 12:31:46 by rpet          #+#    #+#                 */
/*   Updated: 2020/10/26 13:39:21 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
Allowed functions:
memset, malloc, free, write, usleep, gettimeofday
pthread_create
pthread_detach
pthread_join,
pthread_mutex_init
pthread_mutex_destroy
pthread_mutex_lock
pthread_mutex_unlock
*/

#include <pthread.h>
#include <stdlib.h>

int		init_philosophers(t_data *data)
{
	int		i;

	i = 0;
	*data->philo = malloc(sizeof(data->philo) * data->philo_amount);
	while (i < data->philo_amount)
	{
		data->philo[i]->status = THINKING;
		data->philo[i]->left_fork = i;
		data->philo[i]->right_fork = i + 1;
		data->philo[i]->eat_amount = 0;
		i++;
	}
	//printf("shit: [%d]\n", data->philo[i]->left_fork);
	return (1);
}

int		validate_input(t_data *data, char **argv)
{
	if (data->philo_amount <= 0)
		return (philo_error("Invalid input for amount of philosophers\n"));
	if (data->time_to_die <= 0)
		return (philo_error("Invalid input for time to die\n"));
	if (data->time_to_eat <= 0)
		return (philo_error("Invalid input for time to eat\n"));
	if (data->time_to_sleep <= 0)
		return (philo_error("Invalid input for time to sleep\n"));
	if (data->eat_amount <= 0 && argv[5])
		return (philo_error("Invalid input for amount to eat\n"));
	return (1);
}

int		init_data(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (philo_error("Invalid amount of arguments\n"));
	data->philo_amount = philo_atoi(argv[1]);
	data->time_to_die = philo_atoi(argv[2]);
	data->time_to_eat = philo_atoi(argv[3]);
	data->time_to_sleep = philo_atoi(argv[4]);
	if (argv[5])
		data->eat_amount = philo_atoi(argv[5]);
	if (!validate_input(data, argv))
		return (0);
	return (1);
}

int		main(int argc, char **argv)
{
//	pthread_t	philosophers;
	t_data		data;

	if (!init_data(&data, argc, argv))
		return (1);
	if (!init_philosophers(&data))
		return (1);
//	if (!init_philosophers())
//	pthread_create(&philosophers, NULL, , NULL);
//	pthread_join(philosophers, NULL);
	return (0);
}
