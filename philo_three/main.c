/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 09:14:54 by rpet          #+#    #+#                 */
/*   Updated: 2020/11/15 09:33:15 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
**	Main function for the philosophers
*/

int		main(int argc, char **argv)
{
	t_data		data;

	init_data(&data, argc, argv);
	init_mutexes(&data);
	create_processes(&data);
	return (0);
}
