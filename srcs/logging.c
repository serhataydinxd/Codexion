/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 19:16:22 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/23 19:29:08 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/logging.h"
#include <pthread.h>

void	log_event(t_coder *coder, const char *event)
{
	long long	time_now;
	long long	elapsed;

	pthread_mutex_lock(&coder->sim->logger);
	time_now = now_ms();
	elapsed = time_now - coder->sim->sim_time_start;
	printf("%lld %d %s \n", elapsed, coder->id, event);
	pthread_mutex_unlock(&coder->sim->logger);
}
