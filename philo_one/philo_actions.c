/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_actions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 10:40:09 by rpet          #+#    #+#                 */
/*   Updated: 2020/10/31 14:44:47 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

/*
**	Function which writes the status of the philosopher
*/

void	write_status(t_philo *philo, char *status)
{
	t_data	*data;

	data = philo->data;
	if (data->status == DEAD || philo->eat_count == data->max_eat_amount)
		return ;
	pthread_mutex_lock(&data->write);
	philo_putnb(get_time() - data->start_time);
	write(STDOUT_FILENO, " | philo ", 9);
	philo_putnb(philo->philo_num);
	write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, status, philo_strlen(status));
	write(STDOUT_FILENO, "\n", 1);
	pthread_mutex_unlock(&data->write);
}

/*
**	Function where the philosopher thinks and looks for available forks
*/

void	philo_think(t_philo *philo)
{
	write_status(philo, "is thinking");
}

/*
**	Function where the philosopher eats
*/

void	philo_eat(t_philo *philo)
{
	if (philo->data->eat_requirement == true)
		philo->eat_count++;
	write_status(philo, "is eating");
	operation_time(philo->data->time_to_eat);
}

/*
**	Function where the philosophers takes a nap
*/

void	philo_sleep(t_philo *philo)
{
	write_status(philo, "is sleeping");
	operation_time(philo->data->time_to_sleep);
}

/*
**	Function where the philosopher spents time to do an action
*/

void	operation_time(int operation_time)
{
	long	start_sleep;

	start_sleep = get_time();
	while (get_time() - start_sleep < operation_time)
		usleep(10);
}
