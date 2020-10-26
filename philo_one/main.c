/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/23 12:31:46 by rpet          #+#    #+#                 */
/*   Updated: 2020/10/26 19:51:32 by rpet          ########   odam.nl         */
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

void	*philo_loop(void *arg)
{
	t_philo		*philo;

	philo = arg;
	printf("Philo num: [%i]\n", philo->philo_num);
	return (NULL);
}

void	create_thread(t_philo **philo)
{
	int		i;
	t_philo	*cur_philo;

	i = 0;
	printf("amount voor while: [%i]\n", (*philo)->data->philo_amount);
	while (i < (*philo)->data->philo_amount)
	{
		cur_philo = *philo + i;
		printf("amount: [%i]\n", (*philo)->data->philo_amount);
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

int		main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo;

	init_data(&data, argc, argv);
	init_philosophers(&data, &philo);
	create_thread(&philo);
//	pthread_create(&philosophers, NULL, , NULL);
//	pthread_join(philosophers, NULL);
	return (0);
}
