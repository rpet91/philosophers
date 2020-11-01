/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 09:14:54 by rpet          #+#    #+#                 */
/*   Updated: 2020/11/01 10:59:07 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sched.h>
#include <time.h>

/*
**	Function where every philosopher does their actions
*/

void	*philo_loop(void *arg)
{
	t_philo		*philo;
	t_data		*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (data->status != DEAD && philo->eat_count != data->max_eat_amount)
	{
		philo_status_check(philo, "is thinking");
		philo_eat(philo);
		philo_sleep(philo);
	}
	if (philo->eat_count == data->max_eat_amount)
		write_status(philo, "is finished eating");
	if (data->status == DEAD)
		write_status(philo, "died");
	return (NULL);
}

/*
**	Function which creates threads for the amount of philosophers
*/

void	create_thread(t_philo **philo)
{
	int		i;
	t_philo	*cur_philo;

	i = 0;
	while (i < (*philo)->data->philo_amount)
	{
		cur_philo = *philo + i;
		pthread_create(&cur_philo->philo_thread, NULL, philo_loop, cur_philo);
		i++;
	}
	i = 0;
	while (i < (*philo)->data->philo_amount)
	{
		cur_philo = *philo + i;
		pthread_join(cur_philo->philo_thread, NULL);
		i++;
	}
}

/*
**	Main function for the philosophers
*/

int		main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo;

	if (init_data(&data, argc, argv) == -1)
		return (1);
	if (init_philosophers(&data, &philo) == -1)
		return (1);
	if (init_mutexes(&data) == -1)
		return (1);
	create_thread(&philo);
	return (0);
}
