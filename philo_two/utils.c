/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpet <marvin@codam.nl>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 09:37:19 by rpet          #+#    #+#                 */
/*   Updated: 2020/11/15 13:42:04 by rpet          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stddef.h>

void			philo_putnb(unsigned long nb)
{
	char	c;

	if (nb > 9)
		philo_putnb(nb / 10);
	c = (char)(nb % 10 + '0');
	write(STDOUT_FILENO, &c, 1);
}

size_t			philo_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int				philo_error(const char *error)
{
	size_t	len;

	len = philo_strlen(error);
	write(STDERR_FILENO, error, len);
	write(1, "\n", 1);
	return (-1);
}

unsigned long	philo_atoi(const char *str)
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
