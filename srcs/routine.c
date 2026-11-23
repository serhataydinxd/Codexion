/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 15:49:26 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/23 18:46:20 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/routines.h"
#include <pthread.h>

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	pthread_mutex_lock(&coder->sim->state_mutex);
	while (coder->sim->state == WAITING)
		pthread_cond_wait(&coder->sim->state_cond, &coder->sim->state_mutex);
	printf("%d", coder->id);
	return (0);
}

int	create_threads(t_coder *coders, int count)
{
	int	counter;

	counter = 0;
	while (counter < count)
	{
		if (pthread_create(&coders[counter].thread, NULL, coder_routine,
				&coders[counter]))
		{
			if (join_threads(coders, counter))
				return (2);
			return (1);
		}
		counter++;
	}
	return (0);
}

int	join_threads(t_coder *coders, int count)
{
	int	counter;
	int	failed;

	counter = 0;
	failed = 0;
	while (counter < count)
	{
		if (pthread_join(coders[counter].thread, NULL))
			failed = 1;
		counter++;
	}
	return (failed);
}
