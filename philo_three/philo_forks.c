/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_forks.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/08 11:42:45 by rpet          #+#    #+#                 */
/*   Updated: 2020/11/09 16:47:17 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

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
		if (get_time() - philo->eat_time > (unsigned)data->time_to_die)
			data->status = DEAD;
		if (data->status == DEAD)
		{
			write_status(philo, "died");
			sem_post(data->death_lock);
			break ;
		}
		sem_post(data->death_lock);
	}
	return (NULL);
}

/*
**	Function where every philosopher does their actions
*/

static void		philo_loop(t_philo *philo, int philo_num)
{
	t_data		*data;

	data = philo->data;
	philo->philo_num = philo_num;
	if (pthread_create(&data->monitor, NULL, monitor, philo) != 0)
		philo_error("An error occurred duringg creating the monitor thread");
	usleep(100 * (philo->philo_num % 2));
	while (data->status != DEAD && philo->eat_count != data->max_eat_amount)
	{
		philo_status_check(philo, "is thinking");
		philo_eat(philo);
		philo_sleep(philo);
	}
	if (data->status == DEAD)
		exit(1);
	exit(0);
}

/*
**	Function which checks if a philosopher died and terminates every process
*/

static void		health_communicator(t_data *data)
{
	pid_t		pid;
	int			status;
	int			i;

	i = 0;
	while (i < data->philo_amount)
	{
		pid = waitpid(-1, &status, 0);
		if (WEXITED(status) == true)
		{
			if (WEXITSTATUS(status) == 1)
			{
				printf("kaaspap\n");
			}
		}
	}
}

/*
**	Function which creates threads for the amount of philosophers
*/

void			create_forks(t_data *data)
{
	t_philo		philo;
	pid_t		pid;
	int			i;
	int			status;

	init_philosophers(data, &philo);
	i = 0;
	while (i < data->philo_amount)
	{
		pid = fork();
		if (pid == -1)
			philo_error("An error occurred during calling fork");
		else if (pid == 0)
			philo_loop(&philo, i);
		i++;
	}
	health_communicator(data);
}
