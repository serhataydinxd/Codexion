/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 12:17:07 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/27 12:28:02 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/request.h"
#include "../includes/sim.h"
#include <string.h>

int	comp_request(t_request *first, t_request *second, const char *schedular)
{
	if (!strcmp(schedular, "fifo"))
	{
		if (first->arrival < second->arrival)
			return (1);
		return (0);
	}
	if (first->deadline < second->deadline)
		return (1);
	else if (first->deadline == second->deadline)
		return (comp_request(first, second, "fifo"));
	return (0);
}

static int	has_request(t_heap *heap, t_coder *coder)
{
	int	i;

	i = 0;
	while (i < heap->size)
	{
		if (heap->items[i].coder == coder)
			return (1);
		i++;
	}
	return (0);
}

static int	enqueue_pair(t_coder *coder, t_dongle *first, t_dongle *second)
{
	t_request	request;

	if (first->requests.size >= first->requests.capacity
		|| second->requests.size >= second->requests.capacity
		|| has_request(&first->requests, coder)
		|| has_request(&second->requests, coder))
		return (1);
	request.coder = coder;
	request.bypassed = 0;
	request.compiles = coder->compiles;
	request.arrival = next_request_seq(coder->sim);
	request.deadline = coder->last_compile_start
		+ coder->sim->config->time_to_burnout;
	insert_heap(&first->requests, &request);
	insert_heap(&second->requests, &request);
	return (0);
}

int	submit_requests(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;
	int			status;

	first = coder->dongle_left;
	second = coder->dongle_right;
	if (first == second)
		return (1);
	pthread_mutex_lock(&coder->sim->scheduler_mutex);
	status = enqueue_pair(coder, first, second);
	pthread_mutex_unlock(&coder->sim->scheduler_mutex);
	return (status);
}
