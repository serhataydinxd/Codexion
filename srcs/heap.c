/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 13:35:47 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/27 17:41:52 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/heap.h"
#include "../includes/request.h"
#include <stdlib.h>

int	init_dongle_heap(t_heap *heap, const char *scheduler)
{
	heap->capacity = 2;
	heap->items = malloc(heap->capacity * sizeof(t_request));
	if (!heap->items)
		return (1);
	heap->scheduler = scheduler;
	heap->size = 0;
	return (0);
}

int	pop_heap(t_heap *heap, t_request *out)
{
	if (heap->size == 0)
		return (1);
	*out = heap->items[0];
	heap->size--;
	if (heap->size > 0)
		heap->items[0] = heap->items[heap->size];
	return (0);
}

int	insert_heap(t_heap *heap, t_request *request)
{
	t_request	temp;

	if (heap->size < heap->capacity)
	{
		heap->items[heap->size] = *request;
		heap->size++;
		if (heap->size == heap->capacity)
		{
			if (comp_request(&heap->items[1], &heap->items[0], heap->scheduler))
			{
				temp = heap->items[1];
				heap->items[1] = heap->items[0];
				heap->items[0] = temp;
			}
		}
		return (0);
	}
	else
		return (1);
}

int	remove_request(t_heap *heap, struct s_coder *coder)
{
	int	i;

	i = 0;
	while (i < heap->size)
	{
		if (heap->items[i].coder == coder)
		{
			heap->size--;
			heap->items[i] = heap->items[heap->size];
			return (0);
		}
		i++;
	}
	return (1);
}
