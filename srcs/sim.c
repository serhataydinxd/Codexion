/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 19:13:10 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/23 18:07:02 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sim.h"
#include <pthread.h>

void	free_sim(t_sim *sim)
{
	pthread_mutex_destroy(&sim->scheduler_mutex);
	pthread_mutex_destroy(&sim->state_mutex);
	pthread_mutex_destroy(&sim->logger);
	pthread_cond_destroy(&sim->state_cond);
	free_all_dongles(sim->config->number_of_coders, sim->dongles);
	free(sim->coders);
}

unsigned long long	next_request_seq(t_sim *sim)
{
	unsigned long long	sequence;

	pthread_mutex_lock(&sim->state_mutex);
	sequence = sim->next_arrival++;
	pthread_mutex_unlock(&sim->state_mutex);
	return (sequence);
}

static int	init_sync(t_sim *sim)
{
	if (pthread_mutex_init(&sim->state_mutex, NULL))
		return (1);
	if (!pthread_mutex_init(&sim->logger, NULL))
	{
		if (!pthread_mutex_init(&sim->scheduler_mutex, NULL))
		{
			if (!pthread_cond_init(&sim->state_cond, NULL))
				return (0);
			pthread_mutex_destroy(&sim->scheduler_mutex);
		}
		pthread_mutex_destroy(&sim->logger);
	}
	pthread_mutex_destroy(&sim->state_mutex);
	return (1);
}

int	init_sim(t_sim *sim, t_config *config, t_coder *coders, t_dongle *dongles)
{
	int	counter;

	counter = 0;
	sim->state = WAITING;
	sim->next_arrival = 0;
	sim->config = config;
	sim->coders = coders;
	sim->dongles = dongles;
	while (counter < config->number_of_coders)
	{
		coders[counter].sim = sim;
		counter++;
	}
	if (init_sync(sim))
		return (1);
	sim->sim_time_start = 0;
	return (0);
}
