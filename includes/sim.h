/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 19:05:53 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/22 19:45:30 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIM_H
# define SIM_H

# include "coder.h"
# include "config.h"
# include "dongle.h"
# include "time.h"
# include <pthread.h>

typedef struct s_sim
{
	int				sim_active;
	pthread_mutex_t	stop_mutex;
	t_config		*config;
	long long		sim_time_start;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_mutex_t	logger;
}					t_sim;
void				free_sim(t_sim *sim);
int					init_sim(t_sim *sim, t_config *config, t_coder *coders,
						t_dongle *dongles);

#endif
