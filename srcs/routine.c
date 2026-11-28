/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 15:49:26 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/27 12:16:21 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/logging.h"
#include "../includes/routines.h"
#include <pthread.h>

static void	take_single_dongle(t_coder *coder)
{
	t_dongle	*dongle;

	dongle = coder->dongle_left;
	pthread_mutex_lock(&dongle->mutex);
	if (dongle->state == AVAILABLE && now_ms() >= dongle->available_at_ms)
	{
		dongle->state = TAKEN;
		pthread_mutex_unlock(&dongle->mutex);
		log_event(coder, "has taken a dongle");
		return ;
	}
	pthread_mutex_unlock(&dongle->mutex);
}

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
	pthread_mutex_unlock(&coder->sim->state_mutex);
	if (coder->dongle_left == coder->dongle_right)
	{
		take_single_dongle(coder);
		return (0);
	}
	run_cycles(coder);
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
