/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 00:02:19 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/11/13 00:48:56 by ktsukamo         ###   ########.fr       */
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

int	validate_death_state(t_philo *philo)
{
	pthread_mutex_lock(&((t_dining *)philo->ptr_dining)->alive_lock);
	if (((t_dining *)philo->ptr_dining)->is_alive == IS_DEAD)
	{
		pthread_mutex_unlock(&((t_dining *)philo->ptr_dining)->alive_lock);
		return (IS_DEAD);
	}
	pthread_mutex_unlock(&((t_dining *)philo->ptr_dining)->alive_lock);
	pthread_mutex_lock(&((t_dining *)philo->ptr_dining)->all_ate_lock);
	if (((t_dining *)philo->ptr_dining)->all_ate == ATE)
	{
		pthread_mutex_unlock(&((t_dining *)philo->ptr_dining)->all_ate_lock);
		return (IS_DEAD);
	}
	pthread_mutex_unlock(&((t_dining *)philo->ptr_dining)->all_ate_lock);
	return (IS_ALIVE);
}
