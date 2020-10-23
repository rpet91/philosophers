/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/23 12:31:46 by rpet          #+#    #+#                 */
/*   Updated: 2020/10/23 14:05:25 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	*myturn(void *arg)
{
	int		i; 

	(void) arg;
	i = 0;
	while (i < 8)
	{
		sleep(1);
		printf("My Turn!\n");
		i++;
	}
	return (NULL);
}

void	yourturn(void)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		sleep(2);
		printf("Your Turn!\n");
		i++;
	}
}

int		main(void)
{
	pthread_t	newthread;

	pthread_create(&newthread, NULL, myturn, NULL);
	yourturn();
	pthread_join(newthread, NULL);
	return (0);
}
