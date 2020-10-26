/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/23 12:31:46 by rpet          #+#    #+#                 */
/*   Updated: 2020/10/26 15:51:38 by rpet          ########   odam.nl         */
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

int		main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philosophers;

	init_data(&data, argc, argv);
	init_philosophers(&data, &philosophers);
//	pthread_create(&philosophers, NULL, , NULL);
//	pthread_join(philosophers, NULL);
	return (0);
}
