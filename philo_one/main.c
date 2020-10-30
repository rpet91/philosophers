/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/23 12:31:46 by rpet          #+#    #+#                 */
/*   Updated: 2020/10/29 13:46:03 by rpet             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <sys/types.h>
#include <sched.h>
#include <time.h>

/*
**	Function which get called for every created pthread. The life of every philosopher
*/

void	*philo_loop(void *arg)
{
	t_philo		*philo;
	int		i = 0;

	philo = arg;
	(void) philo;
//	printf("Philo num: [%i]\n", philo->philo_num);
	while (1)//philo->philo_num)
	{
		if (i >= 100000)
			return (NULL);
		//pthread_mutex_lock(&philo->data->mutex);
		i++;
		//pthread_mutex_unlock(&philo->data->mutex);
		printf("i: [%i]\n", i);
	}
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

	init_data(&data, argc, argv);
	init_philosophers(&data, &philo);
	init_mutexes(&data);
	create_thread(&philo);
	return (0);
}
