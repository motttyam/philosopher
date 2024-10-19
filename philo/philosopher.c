/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:08:16 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/10/19 22:34:23 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*th_philosopher(void *philo)
{
	// test
	if (((t_philo *)philo)->philo_id % 2 != 0)
		usleep(500);
	// printf("[%d] thread created\n", ((t_philo *)philo)->philo_id);
	for (int i = 0; i < 10; i++)
	{
		ft_eat(philo);
		ft_sleep(philo);
	}
	// printf("[%d] thread finished\n", ((t_philo *)philo)->philo_id);
	return (NULL);
}

void	ft_eat(t_philo *philo)
{
	// right forkの取得
	while (1)
	{
		if (philo->r_fork->fork_state == DIRTY)
		{
			philo->r_fork->fork_state = CLEAN;
			pthread_mutex_lock(&philo->r_fork->lock);
			printf("%ld %d has taken a %d fork\n", timestamp(philo),
				philo->philo_id, philo->r_fork->fork_id);
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
			printf("%ld %d has taken a %d fork\n", timestamp(philo),
				philo->philo_id, philo->l_fork->fork_id);
			break ;
		}
		if (philo->think_flag == NOT_THINK)
		{
			printf("%ld %d is thinking\n", timestamp(philo), philo->philo_id);
			philo->think_flag = THINKING;
		}
		usleep(10);
	}
	// left forkの取得
	printf("%ld %d is eating\n", timestamp(philo), philo->philo_id);
	usleep(((t_dining *)philo->ptr_dining)->time_to_eat * 1000);
	// mutexをlockし、think_flagを初期化する
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
