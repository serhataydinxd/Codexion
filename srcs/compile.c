/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/28 00:00:00 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/28 00:00:00 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/routines.h"
#include "../includes/logging.h"
#include "../includes/wait.h"

static int	wait_for_pair(t_coder *coder)
{
	if (wait_ms(coder->sim, 0) || submit_requests(coder))
		return (1);
	while (!wait_ms(coder->sim, 0))
	{
		if (!try_take_pair(coder))
			return (0);
		if (wait_ms(coder->sim, 1))
			return (1);
	}
	return (1);
}

static int	start_compile(t_coder *coder)
{
	long long	now;

	pthread_mutex_lock(&coder->sim->state_mutex);
	now = now_ms();
	if (coder->sim->state != RUNNING || now - coder->last_compile_start
		>= coder->sim->config->time_to_burnout)
	{
		pthread_mutex_unlock(&coder->sim->state_mutex);
		return (1);
	}
	coder->last_compile_start = now;
	pthread_mutex_unlock(&coder->sim->state_mutex);
	log_event(coder, "has taken a dongle");
	log_event(coder, "has taken a dongle");
	log_event(coder, "is compiling");
	return (0);
}

int	compile_once(t_coder *coder)
{
	int	interrupted;

	if (wait_for_pair(coder))
		return (1);
	if (start_compile(coder))
	{
		release_pair(coder);
		return (1);
	}
	interrupted = wait_ms(coder->sim, coder->sim->config->time_to_compile);
	release_pair(coder);
	pthread_mutex_lock(&coder->sim->state_mutex);
	if (!interrupted && coder->sim->state == RUNNING)
		coder->compiles++;
	pthread_mutex_unlock(&coder->sim->state_mutex);
	return (interrupted);
}

void	run_cycles(t_coder *coder)
{
	while (!compile_once(coder))
	{
		if (wait_ms(coder->sim, 0))
			return ;
		log_event(coder, "is debugging");
		if (wait_ms(coder->sim, coder->sim->config->time_to_debug))
			return ;
		log_event(coder, "is refactoring");
		if (wait_ms(coder->sim, coder->sim->config->time_to_refactor))
			return ;
	}
}
