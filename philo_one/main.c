/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/23 12:31:46 by rpet          #+#    #+#                 */
/*   Updated: 2020/10/26 17:04:21 by rpet          ########   odam.nl         */
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

int		main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philosophers;

	init_data(&data, argc, argv);
	init_philosophers(&data, &philosophers);
//	pthread_create(&philosophers, NULL, , NULL);
//	pthread_join(philosophers, NULL);
	return (0);
}
