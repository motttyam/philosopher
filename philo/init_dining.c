/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dining.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:34:26 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/11/09 18:12:01 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_dining(t_dining *dining)
{
	dining->philos = NULL;
	dining->forks = NULL;
	dining->num_of_philos = -1;
	dining->time_to_die = -1;
	dining->time_to_eat = 0;
	dining->time_to_sleep = 0;
	dining->must_eat = -1;
	dining->all_ate = NOT_ATE;
	dining->is_alive = IS_ALIVE;
	pthread_mutex_init(&dining->alive_lock, NULL);
	pthread_mutex_init(&dining->all_ate_lock, NULL);
}

int	init_forks(t_dining *dining)
{
	int	i;

	i = 0;
	dining->forks = (t_fork *)malloc(sizeof(t_fork) * dining->num_of_philos);
	if (dining->forks == NULL)
	{
		printf("fatal error in ini_forks\n");
		return (-1);
	}
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
	dining->philos = (t_philo *)malloc(sizeof(t_philo) * dining->num_of_philos);
	if (dining->philos == NULL)
		return (printf("fatal error in init_philosopher\n"), -1);
	else
	{
		while (i < dining->num_of_philos)
		{
			init_each_philosopher(dining, &i);
			i++;
		}
	}
	return (0);
}

void	init_each_philosopher(t_dining *dining, int *i)
{
	dining->philos[*i].philo_id = *i;
	dining->philos[*i].think_flag = NOT_THINK;
	dining->philos[*i].meal_timelog = 0;
	pthread_mutex_init(&dining->philos[*i].alive_lock, NULL);
	pthread_mutex_init(&dining->philos[*i].eaten_count_lock, NULL);
	pthread_mutex_init(&dining->philos[*i].meal_timelog_lock, NULL);
	dining->philos[*i].ptr_dining = (void *)dining;
	dining->philos[*i].eaten_count = 0;
	dining->philos[*i].is_alive = IS_ALIVE;
	dining->philos[*i].r_fork = &dining->forks[*i];
	if (*i + 1 == dining->num_of_philos)
		dining->philos[*i].l_fork = &dining->forks[0];
	else
		dining->philos[*i].l_fork = &dining->forks[*i + 1];
}
