/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:44:20 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/11/09 18:31:38 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_philosophers(t_dining *dining)
{
	int		i;
	int		ate;
	t_philo	*philo;

	while (1)
	{
		i = 0;
		ate = 0;
		while (i < dining->num_of_philos)
		{
			philo = &dining->philos[i];
			if (monitor_philosopher_death_state(dining, philo) == 1)
				return ;
			pthread_mutex_lock(&philo->eaten_count_lock);
			if (dining->must_eat != -1
				&& dining->must_eat <= philo->eaten_count)
				ate++;
			pthread_mutex_unlock(&philo->eaten_count_lock);
			i++;
		}
		if (monitor_philosopher_eat_state(dining, ate) == 1)
			return ;
		usleep(10);
	}
}

int	monitor_philosopher_death_state(t_dining *dining, t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_timelog_lock);
	if (dining->time_to_die <= timestamp(philo) - philo->meal_timelog)
	{
		pthread_mutex_unlock(&philo->meal_timelog_lock);
		pthread_mutex_lock(&dining->alive_lock);
		pthread_mutex_lock(&philo->alive_lock);
		philo->is_alive = IS_DEAD;
		dining->is_alive = IS_DEAD;
		pthread_mutex_unlock(&philo->alive_lock);
		pthread_mutex_unlock(&dining->alive_lock);
		printf("%ld %d died\n", timestamp(philo), philo->philo_id);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_timelog_lock);
	return (0);
}

int	monitor_philosopher_eat_state(t_dining *dining, int ate)
{
	if (ate == dining->num_of_philos)
	{
		pthread_mutex_lock(&dining->all_ate_lock);
		dining->all_ate = ATE;
		pthread_mutex_unlock(&dining->all_ate_lock);
		return (1);
	}
	return (0);
}
