/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:18:27 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/22 15:56:21 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dongle.h"

static int	init_dongle(t_dongle *dongle, const char *scheduler, int id)
{
	if (pthread_mutex_init(&dongle->mutex, NULL))
		return (1);
	if (init_dongle_heap(&dongle->requests, scheduler))
	{
		pthread_mutex_destroy(&dongle->mutex);
		return (1);
	}
	dongle->state = AVAILABLE;
	dongle->id = id;
	dongle->available_at_ms = 0;
	return (0);
}

void	free_all_dongles(int counter, t_dongle *all)
{
	int	a;

	a = 0;
	while (a < counter)
	{
		pthread_mutex_destroy(&all[a].mutex);
		free(all[a].requests.items);
		a++;
	}
	free(all);
}

int	init_all_dongles(int count, t_dongle **arr_dongle, const char *scheduler)
{
	t_dongle	*all;
	int			counter;

	all = malloc(count * sizeof(t_dongle));
	if (!all)
		return (1);
	counter = 0;
	while (counter < count)
	{
		if (init_dongle(&all[counter], scheduler, counter))
		{
			free_all_dongles(counter, all);
			return (1);
		}
		counter++;
	}
	*arr_dongle = all;
	return (0);
}
