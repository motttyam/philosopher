/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 00:02:19 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/11/04 00:02:29 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timestamp(t_philo *philo)
{
	struct timeval	tv;
	long			current_time;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000L) + (tv.tv_usec / 1000L);
	return (current_time - ((t_dining *)philo->ptr_dining)->start_time);
}
