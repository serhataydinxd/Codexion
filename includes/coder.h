/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 16:29:11 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/22 17:02:47 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include "dongle.h"
# include <pthread.h>
# include <stdlib.h>

typedef struct s_coder
{
	int			id;
	pthread_t	thread;
	t_dongle	*dongle_left;
	t_dongle	*dongle_right;
	int			compiles;
	long long	last_compile_start;
}				t_coder;

int				init_all_coders(int count, t_dongle *arr_dongle,
					t_coder **arr_coder);

#endif
