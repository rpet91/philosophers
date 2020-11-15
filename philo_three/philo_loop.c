/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_loop.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/08 11:42:45 by rpet          #+#    #+#                 */
/*   Updated: 2020/11/15 14:21:12 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

/*
**	Function which checks if a philosopher dies while waiting or sleeping
*/

static void		*monitor(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (philo->eat_count != data->max_eat_amount)
	{
		sem_wait(data->death_lock);
		if (get_time() - philo->eat_time >= (unsigned)data->time_to_die)
		{
			write_status(philo, "died");
			data->status = DEAD;
			sem_post(data->death_lock);
			exit(1);
		}
		sem_post(data->death_lock);
	}
	return (NULL);
}

/*
**	Function where every philosopher does their actions
*/

void			philo_loop(t_philo *philo, int philo_num)
{
	t_data		*data;

	data = philo->data;
	philo->philo_num = philo_num;
	if (pthread_create(&data->monitor, NULL, monitor, philo) != 0)
		philo_error("An error occurred duringg creating the monitor thread");
	usleep(100 * (philo->philo_num % 2));
	while (data->status != DEAD && philo->eat_count != data->max_eat_amount)
	{
		write_status(philo, "is thinking");
		philo_eat(philo);
		philo_sleep(philo);
	}
	exit(0);
}
