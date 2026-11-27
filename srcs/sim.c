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

static int	destroy_mutex(t_sim *sim, int which)
{
	if (which == 2)
	{
		pthread_mutex_destroy(&sim->state_mutex);
	}
	else if (which == 3)
	{
		pthread_mutex_destroy(&sim->state_mutex);
		pthread_mutex_destroy(&sim->logger);
	}
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
	if (pthread_mutex_init(&sim->state_mutex, NULL))
		return (destroy_mutex(sim, 1));
	if (pthread_mutex_init(&sim->logger, NULL))
		return (destroy_mutex(sim, 2));
	if (pthread_cond_init(&sim->state_cond, NULL))
		return (destroy_mutex(sim, 3));
	sim->sim_time_start = 0;
	return (0);
}
