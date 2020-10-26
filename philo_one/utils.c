/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 09:37:19 by rpet          #+#    #+#                 */
/*   Updated: 2020/10/26 13:06:33 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdint.h>

size_t	philo_strlen(char *str)
{
	int		len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int		philo_error(char *error)
{
	int		len;

	len = philo_strlen(error);
	write(2, error, len);
	return (0);
}

int64_t	philo_atoi(char *str)
{
	int			i;
	uint64_t	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		ret = 10 * ret + str[i] - '0';
		i++;
	}
	return (ret);
}
