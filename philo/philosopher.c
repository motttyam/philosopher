/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:08:16 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/11/16 18:28:12 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	while (1)
	{
		if (validate_death_state(philo) == IS_DEAD)
			return (1);
		if (take_a_fork(philo, philo->r_fork) == 1)
		{
			if (take_a_fork(philo, philo->l_fork) == 1)
				return (0);
			break ;
		}
		if (think(philo) == 1)
			return (1);
		usleep(SLEEP_INTERVAL);
	}
	while (1)
	{
		if (validate_death_state(philo) == IS_DEAD)
			return (1);
		if (take_a_fork(philo, philo->l_fork) == 1)
			break ;
		if (think(philo) == 1)
			return (1);
		usleep(SLEEP_INTERVAL);
	}
	return (0);
}

int	take_a_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->lock);
	if (fork->fork_state == DIRTY)
	{
		fork->fork_state = CLEAN;
		pthread_mutex_unlock(&fork->lock);
		print_log("has taken a fork\n", philo);
		return (1);
	}
	pthread_mutex_unlock(&fork->lock);
	return (0);
}

int	think(t_philo *philo)
{
	if (philo->think_flag == NOT_THINK)
	{
		printf("%ld %d ", timestamp(philo), philo->philo_id);
		print_log("is thinking\n", philo);
		philo->think_flag = THINKING;
	}
	return (0);
}

int	eat(t_philo *philo)
{
	if (validate_death_state(philo) == IS_DEAD)
		return (1);
	pthread_mutex_lock(&philo->meal_timelog_lock);
	philo->meal_timelog = timestamp(philo);
	pthread_mutex_unlock(&philo->meal_timelog_lock);
	print_log("is eating\n", philo);
	precise_usleep(((t_dining *)philo->ptr_dining)->time_to_eat * 1000, philo);
	pthread_mutex_lock(&philo->r_fork->lock);
	philo->r_fork->fork_state = DIRTY;
	pthread_mutex_unlock(&philo->r_fork->lock);
	pthread_mutex_lock(&philo->l_fork->lock);
	philo->l_fork->fork_state = DIRTY;
	pthread_mutex_unlock(&philo->l_fork->lock);
	philo->think_flag = NOT_THINK;
	pthread_mutex_lock(&philo->eaten_count_lock);
	philo->eaten_count++;
	pthread_mutex_unlock(&philo->eaten_count_lock);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (validate_death_state(philo) == IS_DEAD)
		return (1);
	print_log("is sleeping\n", philo);
	precise_usleep(((t_dining *)philo->ptr_dining)->time_to_sleep * 1000,
		philo);
	return (0);
}
