/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 00:00:00 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/22 15:56:35 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_H
# define DONGLE_H

# include "heap.h"
# include <pthread.h>
# include <stdlib.h>

typedef enum e_dongle_state
{
	AVAILABLE,
	TAKEN,
	COOLDOWN
}					t_dongle_state;

typedef struct s_dongle
{
	int				id;
	t_dongle_state	state;
	pthread_mutex_t	mutex;
	long long		available_at_ms;
	t_heap			requests;
}					t_dongle;

int					init_all_dongles(int count, t_dongle **arr_dongle,
						const char *scheduler);
void				free_all_dongles(int counter, t_dongle *all);

#endif
