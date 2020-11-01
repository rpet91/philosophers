/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 09:14:54 by rpet          #+#    #+#                 */
/*   Updated: 2020/11/01 14:33:39 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sched.h>
#include <time.h>

/*static void		*monitor(void *arg)
{
	t_data		*data;

	data = (t_data *)arg;
	printf("kaas\n");
	return (NULL);
}*/

/*
**	Function where every philosopher does their actions
*/

static void		*philo_loop(void *arg)
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
		write_status(philo, "has finished eating");
	return (NULL);
}

/*
**	Function which creates threads for the amount of philosophers
*/

static int		create_threads(t_philo **philo)
{
	int		i;
	t_philo	*cur;

	i = 0;
	while (i < (*philo)->data->philo_amount)
	{
		cur = *philo + i;
		if (pthread_create(&cur->philo_thread, NULL, philo_loop, cur) != 0)
			return (philo_error("An error occurred during creating threads"));
		i++;
	}
//	if (pthread_create(&(*philo)->data->monitor, NULL, monitor, (*philo)->data) != 0)
//		return (philo_error("An error occurred during creating monitor"));
	i = 0;
	while (i < (*philo)->data->philo_amount)
	{
		cur = *philo + i;
		pthread_join(cur->philo_thread, NULL);
		i++;
	}
//	pthread_join((*philo)->data->monitor, NULL);
	if ((*philo)->data->status == DEAD)
		write_status(*philo, "died");
	return (0);
}

/*
**	Main function for the philosophers
*/

int				main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo;

	if (init_data(&data, argc, argv) == -1)
		return (1);
	if (init_mutexes(&data) == -1)
		return (1);
	if (init_philosophers(&data, &philo) == -1)
		return (1);
	if (create_threads(&philo) == -1)
		return (1);
	return (0);
}
