/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_philosopher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:08:16 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/09/06 10:43:56 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	int	i;

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
			// dining->philos[i].l_fork = NULL;
			// dining->philos[i].r_fork = NULL;
            dining->philos[i].ptr_dining = (void *)dining;
			dining->philos[i].eaten_count = 0;
			dining->philos[i].is_alive = IS_ALIVE;
			printf("i:%d\n", i);
			i++;
		}
	}
	return (0);
}

void	*th_philosopher(void *philo)
{
	// test
	// if (((t_philo *)philo)->philo_id % 2 == 0)
	printf("[%d] thread created\n", ((t_philo *)philo)->philo_id);
	
    // eat();
	// sleep();
	// think();
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
	dining->start_time = dining->tv.tv_sec + dining->tv.tv_usec;
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
    		printf("thread[%d] created in main\n", i);
			usleep(1);
        }
		else
		{
    		perror("pthread_create failed");
    		return;
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