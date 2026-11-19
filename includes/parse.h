/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 16:06:00 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/19 17:20:09 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "config.h"
# include <stdlib.h>
# include <string.h>

int	ft_atoi(const char *str);
int	parse_args(int argc, char **argv, t_config *config);

#endif // !PARSE_H
