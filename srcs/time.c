/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 00:00:00 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/22 16:59:22 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/time.h"
#include <sys/time.h>

long long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
