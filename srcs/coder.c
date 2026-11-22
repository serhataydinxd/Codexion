/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 16:35:15 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/22 17:02:15 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coder.h"
#include <stdlib.h>

int	init_all_coders(int count, t_dongle *arr_dongle, t_coder **arr_coder)
{
	int		counter;
	t_coder	*all;

	counter = 0;
	all = malloc(count * sizeof(t_coder));
	if (!all)
		return (1);
	while (counter < count)
	{
		all[counter].id = counter + 1;
		all[counter].compiles = 0;
		all[counter].dongle_left = &arr_dongle[counter];
		all[counter].dongle_right = &arr_dongle[(counter + 1) % count];
		all[counter].last_compile_start = 0;
		counter++;
	}
	*arr_coder = all;
	return (0);
}
