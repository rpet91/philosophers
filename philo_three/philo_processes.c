/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_processes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 13:57:54 by rpet          #+#    #+#                 */
/*   Updated: 2020/11/15 14:27:30 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
**	Function where all the philosophers/processes get killed
*/

static void		kill_philosophers(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philo_amount)
	{
		if (data->philo_pids[i])
			kill(data->philo_pids[i], SIGKILL);
		i++;
	}
}

/*
**	Function which checks if a philosopher died and terminates every process
*/

static void		wait_for_processes(t_data *data)
{
	pid_t		pid;
	int			status;
	int			i;

	i = 0;
	while (i < data->philo_amount)
	{
		pid = waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
			kill_philosophers(data);
		i++;
	}
}

/*
**	Function which creates threads for the amount of philosophers
*/

void			create_processes(t_data *data)
{
	t_philo		philo;
	pid_t		pid;
	int			i;

	init_philosophers(data, &philo);
	data->philo_pids = malloc(sizeof(pid_t) * data->philo_amount);
	if (!data->philo_pids)
		philo_error("Something went wrong while allocating memory");
	memset(data->philo_pids, 0, data->philo_amount);
	i = 0;
	while (i < data->philo_amount)
	{
		pid = fork();
		if (pid == -1)
		{
			kill_philosophers(data);
			philo_error("An error occurred during calling fork");
		}
		else if (pid == 0)
			philo_loop(&philo, i);
		data->philo_pids[i] = pid;
		i++;
	}
	wait_for_processes(data);
}
