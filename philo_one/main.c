/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 09:14:54 by rpet          #+#    #+#                 */
/*   Updated: 2020/11/08 11:49:13 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
**	Main function for the philosophers
*/

int				main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo;

	if (init_data(&data, argc, argv) == -1)
		return (1);
	if (init_philosophers(&data, &philo) == -1)
		return (1);
	if (init_mutexes(&data) == -1)
		return (1);
	if (create_threads(&philo) == -1)
		return (1);
	return (0);
}
