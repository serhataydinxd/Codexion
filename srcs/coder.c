/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 16:35:15 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/23 18:47:20 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coder.h"
#include "../includes/sim.h"
#include <pthread.h>

int	init_all_coders(int count, t_dongle *arr_dongle, t_coder **arr_coder)
{
	int		counter;
	t_coder	*all;

	counter = 0;
	all = malloc(count * sizeof(t_coder));
	if (!all)
		return (1);
	while (counter < count)
	{
		all[counter].id = counter + 1;
		all[counter].compiles = 0;
		all[counter].dongle_left = &arr_dongle[counter];
		all[counter].dongle_right = &arr_dongle[(counter + 1) % count];
		all[counter].last_compile_start = 0;
		counter++;
	}
	*arr_coder = all;
	return (0);
}

int	set_last_comp(t_sim *sim)
{
	int			counter;
	long long	time_now;

	counter = 0;
	pthread_mutex_lock(&sim->state_mutex);
	time_now = now_ms();
	sim->sim_time_start = time_now;
	while (counter < sim->config->number_of_coders)
	{
		sim->coders[counter].last_compile_start = time_now;
		counter++;
	}
	sim->state = RUNNING;
	pthread_cond_broadcast(&sim->state_cond);
	pthread_mutex_unlock(&sim->state_mutex);
	return (0);
}
