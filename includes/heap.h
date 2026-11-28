/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 00:00:00 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/27 17:39:09 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_H
# define HEAP_H

# include "request.h"

typedef struct s_heap
{
	t_request	*items;
	int			size;
	int			capacity;
	const char	*scheduler;
}				t_heap;

int				init_dongle_heap(t_heap *heap, const char *scheduler);
int				insert_heap(t_heap *heap, t_request *request);
int				remove_request(t_heap *heap, struct s_coder *coder);
int				pop_heap(t_heap *heap, t_request *out);

#endif
