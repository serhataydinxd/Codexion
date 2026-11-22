/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:18:27 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/22 15:23:05 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dongle.h"
#include <pthread.h>

int	init_dongle(t_dongle *dongle)
{
	if (!pthread_mutex_init(&dongle->mutex, NULL))
	{
		dongle->state = AVAILABLE;
		dongle->available_at_ms = 0;
		return (0);
	}
	return (1);
}
