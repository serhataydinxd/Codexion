/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 19:13:10 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/22 21:10:15 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sim.h"
#include <pthread.h>

void	free_sim(t_sim *sim)
{
	pthread_mutex_destroy(&sim->stop_mutex);
	pthread_mutex_destroy(&sim->logger);
	free_all_dongles(sim->config->number_of_coders, sim->dongles);
	free(sim->coders);
}

int	init_sim(t_sim *sim, t_config *config, t_coder *coders, t_dongle *dongles)
{
	sim->sim_active = 1;
	sim->config = config;
	sim->coders = coders;
	sim->dongles = dongles;
	if (pthread_mutex_init(&sim->stop_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&sim->logger, NULL))
	{
		pthread_mutex_destroy(&sim->stop_mutex);
		return (1);
	}
	sim->sim_time_start = 0;
	return (0);
}
