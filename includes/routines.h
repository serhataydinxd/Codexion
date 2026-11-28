/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 16:35:50 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/23 18:09:27 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINES_H
# define ROUTINES_H

# include "coder.h"
# include "sim.h"
# include <stdio.h>

void	*coder_routine(void *arg);
int		create_threads(t_coder *coders, int count);
int		join_threads(t_coder *coders, int count);
int		compile_once(t_coder *coder);
void	run_cycles(t_coder *coder);

#endif
