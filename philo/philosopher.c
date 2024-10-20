/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:08:16 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/10/20 17:06:07 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*th_philosopher(void *philo)
{
	if (((t_philo *)philo)->philo_id % 2 != 0)
		usleep(500);
	for (int i = 0; i < 3; i++)
	{
		ft_think(philo);
		ft_eat(philo);
		ft_sleep(philo);
	}
	return (NULL);
}

void	ft_think(t_philo *philo)
{
	while (1)
	{
		if (philo->r_fork->fork_state == DIRTY)
		{
			philo->r_fork->fork_state = CLEAN;
			pthread_mutex_lock(&philo->r_fork->lock);
			printf("%ld %d has taken a fork\n", timestamp(philo),
				philo->philo_id);
			// printf("%ld %d has taken a %d fork\n", timestamp(philo),
			// 	philo->philo_id, philo->r_fork->fork_id);
			break ;
		}
		if (philo->think_flag == NOT_THINK)
		{
			printf("%ld %d is thinking\n", timestamp(philo), philo->philo_id);
			philo->think_flag = THINKING;
		}
		usleep(10);
	}
	// left_forkの取得
	while (1)
	{
		if (philo->l_fork->fork_state == DIRTY)
		{
			philo->l_fork->fork_state = CLEAN;
			pthread_mutex_lock(&philo->l_fork->lock);
			printf("%ld %d has taken a fork\n", timestamp(philo),
				philo->philo_id);
			// printf("%ld %d has taken a %d fork\n", timestamp(philo),
			// 	philo->philo_id, philo->l_fork->fork_id);
			break ;
		}
		if (philo->think_flag == NOT_THINK)
		{
			printf("%ld %d is thinking\n", timestamp(philo), philo->philo_id);
			philo->think_flag = THINKING;
		}
		usleep(10);
	}
}

void	ft_eat(t_philo *philo)
{
	// 食事を行うので、meal_timeを更新
	philo->meal_timelog = timestamp(philo);
	printf("\nphilo %d meal_timelog: %ld\n", philo->philo_id, philo->meal_timelog);
	// 食事を行う
	printf("%ld %d is eating\n", timestamp(philo), philo->philo_id);
	usleep(((t_dining *)philo->ptr_dining)->time_to_eat * 1000);
	// mutexをunlockし、think_flagを初期化する
	pthread_mutex_unlock(&philo->r_fork->lock);
	philo->r_fork->fork_state = DIRTY;
	pthread_mutex_unlock(&philo->l_fork->lock);
	philo->l_fork->fork_state = DIRTY;
	philo->think_flag = NOT_THINK;
}

void	ft_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", timestamp(philo), philo->philo_id);
	usleep(((t_dining *)philo->ptr_dining)->time_to_sleep * 1000);
	return ;
}
