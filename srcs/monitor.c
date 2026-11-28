/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/28 00:00:00 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/28 00:00:00 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/routines.h"
#include "../includes/wait.h"

static int	all_finished(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->config->number_of_coders)
	{
		if (sim->coders[i].compiles < sim->config->number_of_compiles_required)
			return (0);
		i++;
	}
	return (1);
}

static void	check_sim(t_sim *sim)
{
	int			i;
	long long	now;

	if (all_finished(sim))
	{
		sim->state = STOPPED;
		return ;
	}
	now = now_ms();
	i = -1;
	while (++i < sim->config->number_of_coders)
	{
		if (now - sim->coders[i].last_compile_start
			>= sim->config->time_to_burnout)
		{
			sim->state = STOPPED;
			pthread_mutex_lock(&sim->logger);
			printf("%lld %d burned out\n", now - sim->sim_time_start,
				sim->coders[i].id);
			pthread_mutex_unlock(&sim->logger);
			return ;
		}
	}
}

void	*monitor_routine(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	pthread_mutex_lock(&sim->state_mutex);
	while (sim->state == WAITING)
		pthread_cond_wait(&sim->state_cond, &sim->state_mutex);
	while (sim->state == RUNNING)
	{
		check_sim(sim);
		pthread_mutex_unlock(&sim->state_mutex);
		if (wait_ms(sim, 1))
			return (0);
		pthread_mutex_lock(&sim->state_mutex);
	}
	pthread_mutex_unlock(&sim->state_mutex);
	return (0);
}

void	stop_sim(t_sim *sim)
{
	pthread_mutex_lock(&sim->state_mutex);
	sim->state = STOPPED;
	pthread_cond_broadcast(&sim->state_cond);
	pthread_mutex_unlock(&sim->state_mutex);
}

int	run_sim(t_sim *sim)
{
	pthread_t	monitor;
	int			status;

	status = create_threads(sim->coders, sim->config->number_of_coders);
	if (status)
		return (status);
	if (pthread_create(&monitor, NULL, monitor_routine, sim))
	{
		stop_sim(sim);
		if (join_threads(sim->coders, sim->config->number_of_coders))
			return (2);
		return (1);
	}
	set_last_comp(sim);
	status = pthread_join(monitor, NULL);
	if (status)
		stop_sim(sim);
	if (join_threads(sim->coders, sim->config->number_of_coders) || status)
		return (2);
	return (0);
}
