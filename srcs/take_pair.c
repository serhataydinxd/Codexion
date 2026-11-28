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

static int	pair_ready(t_coder *coder, long long now)
{
	return (coder->dongle_left->state != TAKEN
		&& coder->dongle_right->state != TAKEN
		&& now >= coder->dongle_left->available_at_ms
		&& now >= coder->dongle_right->available_at_ms);
}

static int	request_allowed(t_coder *coder, t_heap *heap, long long now)
{
	if (heap->size == 0)
		return (0);
	if (heap->items[0].coder == coder)
		return (1);
	if (heap->size != 2 || heap->items[1].coder != coder
		|| heap->items[0].bypassed
		|| heap->items[1].deadline > heap->items[0].deadline
		|| heap->items[1].compiles > heap->items[0].compiles)
		return (0);
	return (!pair_ready(heap->items[0].coder, now));
}

static int	claim_pair(t_coder *coder, t_dongle *first, t_dongle *second)
{
	long long	now;

	now = now_ms();
	if (!pair_ready(coder, now)
		|| !request_allowed(coder, &first->requests, now)
		|| !request_allowed(coder, &second->requests, now))
		return (1);
	if (first->requests.items[0].coder != coder)
		first->requests.items[0].bypassed = 1;
	if (second->requests.items[0].coder != coder)
		second->requests.items[0].bypassed = 1;
	first->state = TAKEN;
	second->state = TAKEN;
	remove_request(&first->requests, coder);
	remove_request(&second->requests, coder);
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
	pthread_mutex_lock(&coder->sim->scheduler_mutex);
	status = claim_pair(coder, first, second);
	pthread_mutex_unlock(&coder->sim->scheduler_mutex);
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
	pthread_mutex_lock(&coder->sim->scheduler_mutex);
	available_at = now_ms() + coder->sim->config->dongle_cooldown;
	first->state = COOLDOWN;
	second->state = COOLDOWN;
	first->available_at_ms = available_at;
	second->available_at_ms = available_at;
	pthread_mutex_unlock(&coder->sim->scheduler_mutex);
}
