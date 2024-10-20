/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dining.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:34:26 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/10/20 17:00:25 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_dining(t_dining *dining)
{
	dining->philos = NULL;
	dining->forks = NULL;
	dining->num_of_philos = 0;
	dining->time_to_die = 0;
	dining->time_to_eat = 0;
	dining->time_to_sleep = 0;
	dining->must_eat = 0;
	dining->all_ate = NOT_ATE;
	dining->is_alive = IS_ALIVE;
}

int	init_forks(t_dining *dining)
{
	int	i;

	i = 0;
	dining->forks = (t_fork *)malloc(sizeof(t_fork) * dining->num_of_philos);
	// malloc 失敗した時の処理
	if (dining->forks == NULL)
	{
		printf("fatal error in ini_forks\n");
		return (-1);
	}
	// 成功したときは構造体の配列を初期化する
	else
	{
		memset(dining->forks, 0, sizeof(t_fork) * dining->num_of_philos);
		while (i < dining->num_of_philos)
		{
			dining->forks[i].fork_id = i;
			dining->forks[i].fork_state = DIRTY;
			pthread_mutex_init(&dining->forks[i].lock, NULL);
			i++;
		}
	}
	return (0);
}

int	init_philosophers(t_dining *dining)
{
	int i;

	i = 0;
	// 必要か不明だが、200以上は弾いておく
	if (dining->num_of_philos >= 200)
		return (arguments_error(0, NULL), test_handle_arguments(dining), -1);
	dining->philos = (t_philo *)malloc(sizeof(t_philo) * dining->num_of_philos);
	// malloc 失敗した時の処理
	if (dining->philos == NULL)
	{
		printf("fatal error in init_philosopher\n");
		return (-1);
	}
	// 成功したときは構造体の配列を初期化する
	else
	{
		memset(dining->philos, 0, sizeof(t_philo) * dining->num_of_philos);
		while (i < dining->num_of_philos)
		{
			dining->philos[i].philo_id = i;
			dining->philos[i].think_flag = NOT_THINK;
			dining->philos[i].meal_timelog = 0;
			dining->philos[i].ptr_dining = (void *)dining;
			dining->philos[i].eaten_count = 0;
			dining->philos[i].is_alive = IS_ALIVE;
			dining->philos[i].r_fork = &dining->forks[i];
			if (i + 1 == dining->num_of_philos)
				dining->philos[i].l_fork = &dining->forks[0];
			else
				dining->philos[i].l_fork = &dining->forks[i + 1];
			i++;
		}
	}
	return (0);
}