/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 17:01:16 by rpet          #+#    #+#                 */
/*   Updated: 2020/11/09 16:46:05 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <semaphore.h>

/*
**	Creates a struct for every philosopher
*/

void		init_philosophers(t_data *data, t_philo *philo)
{
	philo->philo_num = 0;
	philo->eat_count = 0;
	philo->eat_time = get_time();
	philo->data = data;
}

/*
**	Initialises the mutex locks for writing status and forks
*/

void		init_mutexes(t_data *data)
{
	sem_unlink("death_lock");
	data->death_lock = sem_open("death_lock", O_CREAT, 0644, 1);
	if (data->death_lock == SEM_FAILED)
		philo_error("An error occurred during sem open death_lock");
	sem_unlink("write_lock");
	data->write_lock = sem_open("write_lock", O_CREAT, 0644, 1);
	if (data->write_lock == SEM_FAILED)
		philo_error("An error occurred during sem open write_lock");
	sem_unlink("fork_lock");
	data->fork_lock = sem_open("fork_lock", O_CREAT, 0644, data->philo_amount);
	if (data->fork_lock == SEM_FAILED)
		philo_error("An error occurred during sem open fork_lock");
}

/*
**	Checks if the given input is valid
*/

static void	validate_input(t_data *data)
{
	if (data->philo_amount <= 1)
		philo_error("Invalid input for amount of philosophers");
	if (data->time_to_die <= 0)
		philo_error("Invalid input for time to die");
	if (data->time_to_eat <= 0)
		philo_error("Invalid input for time to eat");
	if (data->time_to_sleep <= 0)
		philo_error("Invalid input for time to sleep");
	if (data->max_eat_amount <= 0 && data->eat_requirement == true)
		philo_error("Invalid input for amount to eat");
}

/*
**	Saves all the input in a data struct
*/

void		init_data(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		philo_error("Invalid amount of arguments");
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
	validate_input(data);
}
