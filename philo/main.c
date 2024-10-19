/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:58:32 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/10/19 21:31:30 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_dining dining;
	
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
	int i;
	t_philo *philo;

	i = 0;
	// fork と philos のメモリを動的に取得
	if (init_forks(dining) == -1 || init_philosophers(dining) == -1)
		return ;
	// test
	print_dining(dining);

	// 現在の時刻を取得
	dining->start_time = timestamp(&dining->philos[i]);
	
	while (i < dining->num_of_philos)
	{
		philo = &dining->philos[i];
		if (pthread_create(&dining->philos[i].th, NULL, th_philosopher,
				philo) == 0)
		{	
		}
		else
		{
			perror("pthread_create failed");
			return ;
		}
		i++;
	}
	// ここでjoinしてあげると、正しく動く
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
