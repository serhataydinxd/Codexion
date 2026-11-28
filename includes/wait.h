/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/28 00:00:00 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/28 00:00:00 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WAIT_H
# define WAIT_H

# include "sim.h"
# include <unistd.h>

int	wait_ms(t_sim *sim, long long duration);

#endif
