#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define COUNT_TO 100000
#define MAX_CORES 12

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
long long i = 0;

void	*count(void *arg)
{
	for (;;)
	{
		if (i >= COUNT_TO)
		{
			return (NULL);
		}
		i++;
		printf("i = %lli\n", i);
	}
	return (NULL);
}


int		main(void)
{
	pthread_t *group = malloc(sizeof(pthread_t) * MAX_CORES);

	for (int i = 0; i < MAX_CORES; i++)
		pthread_create(&group[i], NULL, count, NULL);
	for (int i = 0; i < MAX_CORES; i++)
		pthread_join(group[i], NULL);
	return (0);
}
