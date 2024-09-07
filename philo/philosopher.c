/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:08:16 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/09/07 17:00:25 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timestamp(t_philo *philo)
{
	struct timeval	tv;
	long			current_time;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (current_time - ((t_dining *)philo->ptr_dining)->start_time);
}

void	ft_eat(t_philo *philo)
{
	int	i;

	i = 0;
	// right forkの取得
	while (1)
	{
		if (philo->r_fork->fork_state == DIRTY)
		{
			philo->r_fork->fork_state = CLEAN;
			pthread_mutex_lock(&philo->r_fork->lock);
			printf("%ld %d has taken a fork\n", timestamp(philo),
				philo->philo_id);
			break;
		}
		if (i++ == 0)
			printf("%ld %d is thinking\n", timestamp(philo), philo->philo_id);
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
			break;
		}
		// if (i++ == 0)
		// 	printf("%ld %d is thinking\n", timestamp(philo), philo->philo_id);
		usleep(10);
	}
	// left forkの取得
	printf("%ld %d is eating\n", timestamp(philo), philo->philo_id);
	usleep(((t_dining *)philo->ptr_dining)->time_to_eat);
	pthread_mutex_unlock(&philo->l_fork->lock);
	philo->l_fork->fork_state = DIRTY;
	pthread_mutex_unlock(&philo->r_fork->lock);
	philo->r_fork->fork_state = DIRTY;
}

void	ft_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", timestamp(philo), philo->philo_id);
	usleep(((t_dining *)philo->ptr_dining)->time_to_sleep);
	return ;
}

void	*th_philosopher(void *philo)
{
	// test
	printf("[%d] thread created\n", ((t_philo *)philo)->philo_id);
	if (((t_philo *)philo)->philo_id % 2 != 0)
		usleep(100);
	ft_eat(philo);
	ft_sleep(philo);
	printf("[%d] thread finished\n", ((t_philo *)philo)->philo_id);
	return (NULL);
}
void	launch_dining_philosopher(t_dining *dining)
{
	int i;
	t_philo *philo;

	i = 0;
	// fork と philos のメモリを動的に取得
	if (init_forks(dining) == -1 || init_philosophers(dining) == -1)
		return ;
	// 現在の時刻を取得
	gettimeofday(&dining->tv, NULL);
	dining->start_time = dining->tv.tv_sec * 1000 + dining->tv.tv_usec / 1000;
	// test関数
	print_dining(dining);
	// threadを立ち上げる（偶数は遅らせるなどしたほうが良い..?）
	while (i < dining->num_of_philos)
	{
		philo = &dining->philos[i];
		if (pthread_create(&dining->philos[i].th, NULL, th_philosopher,
				philo) == 0)
		{
			// detachだと最後のスレッドのみ正しく出力されない
			// pthread_detach(philo->th);
			// printf("thread[%d] created in main\n", i);
			// usleep(1);
		}
		else
		{
			perror("pthread_create failed");
			return ;
		}
		i++;
		// printf("i:%d\n", i);
	}
	// ここでjoinしてあげると、正しく動く
	for (i = 0; i < dining->num_of_philos; i++)
	{
		pthread_join(dining->philos[i].th, NULL);
	}
}