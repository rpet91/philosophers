/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 09:37:19 by rpet          #+#    #+#                 */
/*   Updated: 2020/11/08 11:55:42 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stddef.h>
#include <sys/time.h>

unsigned long	get_time(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void			philo_putnb(unsigned long nb)
{
	char	c;

	if (nb > 9)
		philo_putnb(nb / 10);
	c = (char)(nb % 10 + '0');
	write(STDOUT_FILENO, &c, 1);
}

size_t			philo_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int				philo_error(char *error)
{
	size_t	len;

	len = philo_strlen(error);
	write(STDERR_FILENO, error, len);
	write(1, "\n", 1);
	return (-1);
}

unsigned long	philo_atoi(char *str)
{
	int				i;
	unsigned long	ret;

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
