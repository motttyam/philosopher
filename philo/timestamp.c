/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 00:02:19 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/11/16 16:17:20 by ktsukamo         ###   ########.fr       */
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

void	precise_usleep(useconds_t time)
{
	struct timeval	tv;
	long			end_time;
	long			current_time;

	gettimeofday(&tv, NULL);
	end_time = (tv.tv_sec * 1000000L) + tv.tv_usec + time;
	current_time = (tv.tv_sec * 1000000L) + tv.tv_usec;
	while (end_time > current_time)
	{
		usleep(time / 2);
		if (time > 100)
			time /= 2;
		else
			time = 100;
		gettimeofday(&tv, NULL);
		current_time = (tv.tv_sec * 1000000L) + tv.tv_usec;
	}
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
