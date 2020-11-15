/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_actions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 10:40:09 by rpet          #+#    #+#                 */
/*   Updated: 2020/11/15 13:41:48 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

/*
**	Function which writes the status of the philosopher
*/

void	write_status(t_philo *philo, char *status)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->write_lock);
	if (data->status == DEAD || philo->eat_count == data->max_eat_amount)
	{
		pthread_mutex_unlock(&data->write_lock);
		return ;
	}
	philo_putnb(get_time() - data->start_time);
	write(STDOUT_FILENO, "\t", 1);
	philo_putnb(philo->philo_num);
	write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, status, philo_strlen(status));
	write(STDOUT_FILENO, "\n", 1);
	pthread_mutex_unlock(&data->write_lock);
}

/*
**	Function where the philosopher eats
*/

void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->status == DEAD || philo->eat_count == data->max_eat_amount)
		return ;
	pthread_mutex_lock(philo->fork_one);
	write_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_two);
	write_status(philo, "has taken a fork");
	pthread_mutex_lock(&data->death_lock);
	write_status(philo, "is eating");
	philo->eat_time = get_time();
	pthread_mutex_unlock(&data->death_lock);
	if (data->eat_requirement == true)
		philo->eat_count++;
	operation_time(data->time_to_eat);
	pthread_mutex_unlock(philo->fork_one);
	pthread_mutex_unlock(philo->fork_two);
}

/*
**	Function where the philosophers takes a nap
*/

void	philo_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	write_status(philo, "is sleeping");
	operation_time(data->time_to_sleep);
}

/*
**	Function where the philosopher spents time to do an action
*/

void	operation_time(int operation_time)
{
	unsigned long	start_sleep;

	start_sleep = get_time();
	while (get_time() - start_sleep < (unsigned)operation_time)
		usleep(100);
}
