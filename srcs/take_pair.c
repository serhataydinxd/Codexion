/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_pair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/28 00:00:00 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/28 00:00:00 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coder.h"
#include "../includes/sim.h"
#include "../includes/time.h"

static int	claim_pair(t_coder *coder, t_dongle *first, t_dongle *second)
{
	t_request	request;
	long long	now;

	now = now_ms();
	if (first->state == TAKEN || second->state == TAKEN
		|| now < first->available_at_ms || now < second->available_at_ms
		|| first->requests.size == 0 || second->requests.size == 0)
		return (1);
	if (first->requests.items[0].coder != coder
		|| second->requests.items[0].coder != coder)
		return (1);
	first->state = TAKEN;
	second->state = TAKEN;
	pop_heap(&first->requests, &request);
	pop_heap(&second->requests, &request);
	return (0);
}

int	try_take_pair(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;
	int			status;

	first = coder->dongle_left;
	second = coder->dongle_right;
	if (first == second)
		return (1);
	if (first->id > second->id)
	{
		first = coder->dongle_right;
		second = coder->dongle_left;
	}
	pthread_mutex_lock(&first->mutex);
	pthread_mutex_lock(&second->mutex);
	status = claim_pair(coder, first, second);
	pthread_mutex_unlock(&second->mutex);
	pthread_mutex_unlock(&first->mutex);
	return (status);
}

void	release_pair(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;
	long long	available_at;

	first = coder->dongle_left;
	second = coder->dongle_right;
	if (first == second)
		return ;
	if (first->id > second->id)
	{
		first = coder->dongle_right;
		second = coder->dongle_left;
	}
	pthread_mutex_lock(&first->mutex);
	pthread_mutex_lock(&second->mutex);
	available_at = now_ms() + coder->sim->config->dongle_cooldown;
	first->state = COOLDOWN;
	second->state = COOLDOWN;
	first->available_at_ms = available_at;
	second->available_at_ms = available_at;
	pthread_mutex_unlock(&second->mutex);
	pthread_mutex_unlock(&first->mutex);
}
