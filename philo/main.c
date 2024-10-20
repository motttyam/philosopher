/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:58:32 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/10/20 17:43:46 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_dining	dining;

	// dining構造体をmemsetで初期化
	memset((void *)&dining, 0, sizeof(dining));
	init_dining(&dining);
	// 引数のハンドリング
	if (argc != 5 && argc != 6)
		return (arguments_error(argc, argv), -1);
	// 引数がすべて数字であるかハンドリング
	if (handle_arguments(argc, argv, &dining) == -1)
		return (arguments_error(argc, argv), -1);
	launch_dining_philosopher(&dining);
	// dining構造体はstackで取得しているが、forksとphiloは動的に取得しているためfreeが必要
	if (dining.forks != NULL)
		free(dining.forks);
	if (dining.philos != NULL)
		free(dining.philos);
	// test関数
	// test_handle_arguments(&dining);
	return (0);
}

void	launch_dining_philosopher(t_dining *dining)
{
	int		i;
	t_philo	*philo;

	i = 0;
	// fork と philos のメモリを動的に取得
	if (init_forks(dining) == -1 || init_philosophers(dining) == -1)
		return ;
	// 現在の時刻を取得
	dining->start_time = timestamp(&dining->philos[i]);
	while (i < dining->num_of_philos)
	{
		philo = &dining->philos[i];
		if (pthread_create(&dining->philos[i].th, NULL, th_philosopher,
				philo) != 0)
			return (perror("pthread_create failed"));
		i++;
	}
	while (1)
	{
		i = 0;
		dining->all_ate = 0;
		while (i < dining->num_of_philos)
		{
			philo = &dining->philos[i];
			// 餓死時間 < 現時刻 - 最後の食事時間であれば死亡フラグを立てる
			if (dining->time_to_die < timestamp(philo) - philo->meal_timelog)
			{
				pthread_mutex_lock(&dining->alive_lock);
				pthread_mutex_lock(&philo->alive_lock);
				philo->is_alive = IS_DEAD;
				dining->is_alive = IS_DEAD;
				pthread_mutex_unlock(&philo->alive_lock);
				pthread_mutex_unlock(&dining->alive_lock);
				break ;
			}
			// // 規定食事回数 >= 現在の食事回数であればall_ateフラグを加算する
			// //
			// if (dining->must_eat >= philo->eaten_count)
			// 	dining->all_ate++;
			i++;
		}
		// // 哲学者が規定された回数食事していれば終了(all_ateの数がnum_of_philosと同じ場合、処理を抜ける)
		// if (dining->all_ate == dining->num_of_philos)
		// 	break ;
	}
	for (i = 0; i < dining->num_of_philos; i++)
	{
		pthread_join(dining->philos[i].th, NULL);
	}
}

long	timestamp(t_philo *philo)
{
	struct timeval	tv;
	long			current_time;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000L) + (tv.tv_usec / 1000L);
	return (current_time - ((t_dining *)philo->ptr_dining)->start_time);
}
