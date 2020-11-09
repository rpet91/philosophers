/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_actions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 10:40:09 by rpet          #+#    #+#                 */
/*   Updated: 2020/11/08 15:10:31 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <semaphore.h>

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
	sem_post(data->write_lock);
}

/*
**	Function which checks if the philosopher is alive or done eating
*/

void	philo_status_check(t_philo *philo, char *status)
{
	t_data	*data;

	data = philo->data;
	if (get_time() - philo->eat_time > (unsigned)data->time_to_die)
		data->status = DEAD;
	if (data->status == DEAD || philo->eat_count == data->max_eat_amount)
		return ;
	write_status(philo, status);
}

/*
**	Function where the philosopher eats
*/

void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	sem_wait(data->fork_lock);
	philo_status_check(philo, "has taken a fork");
	sem_wait(data->fork_lock);
	philo_status_check(philo, "has taken a fork");
	philo_status_check(philo, "is eating");
	philo->eat_time = get_time();
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
	if (data->status == DEAD || philo->eat_count == data->max_eat_amount)
		return ;
	philo_status_check(philo, "is sleeping");
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
