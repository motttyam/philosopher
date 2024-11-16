/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:58:32 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/11/13 00:41:58 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_dining	dining;

	init_dining(&dining);
	if (argc != 5 && argc != 6)
		return (arguments_error(argc, argv), -1);
	if (handle_arguments(argc, argv, &dining) == -1)
		return (arguments_error(argc, argv), -1);
	if (handle_dining_conditions(&dining) == -1)
		return (0);
	launch_dining_philosopher(&dining);
	if (dining.forks != NULL)
		free(dining.forks);
	if (dining.philos != NULL)
		free(dining.philos);
	return (0);
}

void	launch_dining_philosopher(t_dining *dining)
{
	int		i;
	t_philo	*philo;

	i = 0;
	if (init_forks(dining) == -1 || init_philosophers(dining) == -1)
		return ;
	dining->start_time = timestamp(&dining->philos[i]);
	while (i < dining->num_of_philos)
	{
		philo = &dining->philos[i];
		if (pthread_create(&dining->philos[i].th, NULL, th_philosopher,
				philo) != 0)
			return (perror("pthread_create failed"));
		i++;
	}
	monitor_philosophers(dining);
	i = 0;
	while (i < dining->num_of_philos)
	{
		pthread_join(dining->philos[i].th, NULL);
		i++;
	}
}

void	*th_philosopher(void *philo)
{
	if (((t_philo *)philo)->philo_id % 2 != 0)
		usleep(500);
	while (1)
	{
		if (take_forks(philo) == 1)
			break ;
		if (eat(philo) == 1)
			break ;
		if (ft_sleep(philo) == 1)
			break ;
	}
	return (NULL);
}
