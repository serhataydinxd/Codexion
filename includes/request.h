/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seraydin@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 00:00:00 by seraydin          #+#    #+#             */
/*   Updated: 2026/11/27 12:06:32 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_H
# define REQUEST_H

struct	s_coder;

typedef struct s_request
{
	struct s_coder		*coder;
	unsigned long long	arrival;
	long long			deadline;
}						t_request;

int						comp_request(t_request *first, t_request *second,
							const char *schedular);
int						submit_requests(struct s_coder *coder);

#endif
