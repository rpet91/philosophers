/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_actions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 10:40:09 by rpet          #+#    #+#                 */
/*   Updated: 2020/11/15 14:30:03 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <semaphore.h>
#include <stdbool.h>

/*
**	Function which writes the status of the philosopher
*/

void	write_status(t_philo *philo, char *status)
{
	t_data	*data;

	data = philo->data;
	sem_wait(data->write_lock);
	philo_putnb(get_time() - data->start_time);
	write(STDOUT_FILENO, "\t", 1);
	philo_putnb(philo->philo_num);
	write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, status, philo_strlen(status));
	write(STDOUT_FILENO, "\n", 1);
	if (!philo_strcmp(status, "died"))
		return ;
	sem_post(data->write_lock);
}

/*
**	Function where the philosopher eats
*/

void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	sem_wait(data->fork_lock);
	write_status(philo, "has taken a fork");
	sem_wait(data->fork_lock);
	write_status(philo, "has taken a fork");
	sem_wait(data->death_lock);
	write_status(philo, "is eating");
	philo->eat_time = get_time();
	sem_post(data->death_lock);
	if (data->eat_requirement == true)
		philo->eat_count++;
	operation_time(data->time_to_eat);
	sem_post(data->fork_lock);
	sem_post(data->fork_lock);
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
		usleep(10);
}
