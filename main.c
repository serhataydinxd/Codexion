/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 14:59:37 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/22 16:01:16 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/config.h"
#include "includes/dongle.h"
#include "includes/parse.h"
#include <pthread.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_config	config;
	t_dongle	*dongles;

	if (parse_args(argc, argv, &config))
	{
		fprintf(stderr, "Invalid arguments\n");
		return (1);
	}
	printf("number_of_coders: %d\n", config.number_of_coders);
	printf("time_to_burnout: %d\n", config.time_to_burnout);
	printf("time_to_compile: %d\n", config.time_to_compile);
	printf("time_to_debug: %d\n", config.time_to_debug);
	printf("time_to_refactor: %d\n", config.time_to_refactor);
	printf("number_of_compiles_required: %d\n",
		config.number_of_compiles_required);
	printf("dongle_cooldown: %d\n", config.dongle_cooldown);
	printf("scheduler: %s\n", config.scheduler);
	if (init_all_dongles(config.number_of_coders, &dongles))
	{
		fprintf(stderr, "Dongle initialization failed\n");
		free_all_dongles(config.number_of_coders, dongles);
		return (1);
	}
	return (0);
}
