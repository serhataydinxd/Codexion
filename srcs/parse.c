/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 16:11:37 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/19 19:07:03 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/config.h"
#include "../includes/parse.h"

static int	check_config(t_config *config)
{
	if (config->number_of_coders < 1)
		return (1);
	if (config->time_to_burnout < 0)
		return (1);
	if (config->time_to_compile < 0)
		return (1);
	if (config->time_to_debug < 0)
		return (1);
	if (config->time_to_refactor < 0)
		return (1);
	if (config->number_of_compiles_required < 1)
		return (1);
	if (config->dongle_cooldown < 0)
		return (1);
	if (!strcmp(config->scheduler, "fifo"))
		config->scheduler = "fifo";
	else if (!strcmp(config->scheduler, "edf"))
		config->scheduler = "edf";
	else
		return (1);
	return (0);
}

int	parse_args(int argc, char **argv, t_config *config)
{
	if (argc != 9)
		return (1);
	config->number_of_coders = ft_atoi(argv[1]);
	config->time_to_burnout = ft_atoi(argv[2]);
	config->time_to_compile = ft_atoi(argv[3]);
	config->time_to_debug = ft_atoi(argv[4]);
	config->time_to_refactor = ft_atoi(argv[5]);
	config->number_of_compiles_required = ft_atoi(argv[6]);
	config->dongle_cooldown = ft_atoi(argv[7]);
	config->scheduler = argv[8];
	return (check_config(config));
}
