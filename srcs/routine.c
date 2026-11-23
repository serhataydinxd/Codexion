/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 15:49:26 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/23 19:30:49 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/logging.h"
#include "../includes/routines.h"
#include <pthread.h>

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	pthread_mutex_lock(&coder->sim->state_mutex);
	while (coder->sim->state == WAITING)
		pthread_cond_wait(&coder->sim->state_cond, &coder->sim->state_mutex);
	if (coder->sim->state == STOPPED)
	{
		pthread_mutex_unlock(&coder->sim->state_mutex);
		return (0);
	}
	log_event(coder, "idfk");
	pthread_mutex_unlock(&coder->sim->state_mutex);
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
			pthread_mutex_lock(&coders[counter].sim->state_mutex);
			coders[counter].sim->state = STOPPED;
			pthread_cond_broadcast(&coders[counter].sim->state_cond);
			pthread_mutex_unlock(&coders[counter].sim->state_mutex);
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
