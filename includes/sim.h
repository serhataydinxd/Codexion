/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 19:05:53 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/23 17:13:47 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIM_H
# define SIM_H

# include "coder.h"
# include "config.h"
# include "dongle.h"
# include "time.h"
# include <pthread.h>

typedef enum e_sim_state
{
	WAITING,
	RUNNING,
	STOPPED
}					t_sim_state;

typedef struct s_sim
{
	t_sim_state			state;
	pthread_mutex_t		state_mutex;
	pthread_cond_t		state_cond;
	t_config			*config;
	long long			sim_time_start;
	t_coder				*coders;
	t_dongle			*dongles;
	pthread_mutex_t		logger;
	pthread_mutex_t		scheduler_mutex;
	unsigned long long	next_arrival;
}					t_sim;
void				free_sim(t_sim *sim);
unsigned long long	next_request_seq(t_sim *sim);
int					init_sim(t_sim *sim, t_config *config, t_coder *coders,
						t_dongle *dongles);

#endif
