/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 13:32:13 by rpet          #+#    #+#                 */
/*   Updated: 2020/11/15 13:32:38 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

unsigned long	get_time(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
