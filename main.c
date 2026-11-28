/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 14:59:37 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/23 18:43:24 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/coder.h"
#include "includes/config.h"
#include "includes/dongle.h"
#include "includes/parse.h"
#include "includes/routines.h"
#include "includes/sim.h"
#include <pthread.h>
#include <stdio.h>

static int	init_resources(t_sim *sim, t_config *config)
{
	t_dongle	*dongles;
	t_coder		*coders;

	if (init_all_dongles(config->number_of_coders, &dongles, config->scheduler))
	{
		fprintf(stderr, "Dongle initialization failed\n");
		return (1);
	}
	if (init_all_coders(config->number_of_coders, dongles, &coders))
	{
		free_all_dongles(config->number_of_coders, dongles);
		fprintf(stderr, "Coder initialization failed\n");
		return (1);
	}
	if (init_sim(sim, config, coders, dongles))
	{
		free_all_dongles(config->number_of_coders, dongles);
		free(coders);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_config	config;
	t_sim		sim;
	int			status;

	if (parse_args(argc, argv, &config))
	{
		fprintf(stderr, "Invalid arguments\n");
		return (1);
	}
	if (init_resources(&sim, &config))
		return (1);
	status = run_sim(&sim);
	if (status)
	{
		if (status == 1)
			free_sim(&sim);
		return (1);
	}
	free_sim(&sim);
	return (0);
}
