/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/28 00:00:00 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/28 00:00:00 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wait.h"

int	wait_ms(t_sim *sim, long long duration)
{
	long long	start;
	int			stopped;

	start = now_ms();
	while (1)
	{
		pthread_mutex_lock(&sim->state_mutex);
		stopped = (sim->state == STOPPED);
		pthread_mutex_unlock(&sim->state_mutex);
		if (stopped)
			return (1);
		if (now_ms() - start >= duration)
			return (0);
		usleep(500);
	}
}
