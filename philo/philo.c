/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:58:32 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/09/05 10:07:41 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int handle_arguments(int argc, char **argv, t_dining *dining)
{
	// char philo,  number_of_philosophers,  time_to_die,  time_to_eat,  time_to_sleep");
	// (number_of_times_each_philosopher_must_eat)
	if(ft_strdigit(argv[1]) == 1 && ft_strdigit(argv[2]) == 1 
		&& ft_strdigit(argv[3]) == 1 && ft_strdigit(argv[4]) == 1)
	{
		dining->num_of_philos = ft_atoi(argv[1]);
		dining->num_of_forks = dining->num_of_philos;
		dining->time_to_die = ft_atoi(argv[2]);
		dining->time_to_eat = ft_atoi(argv[3]);
		dining->time_to_sleep = ft_atoi(argv[4]);
		if(argc == 6 && ft_strdigit(argv[5]) == 1)
			dining->must_eat = ft_atoi(argv[5]);
	}
	else
	{
		return (-1);
	}
	return (0);
}

void init_dining(t_dining *dining)
{
	dining->philos = NULL;
	dining->forks = NULL;
	dining->num_of_philos = 0;
	dining->num_of_forks = 0;
	dining->time_to_die = 0;
	dining->time_to_eat = 0;
	dining->time_to_sleep = 0;
	dining->must_eat = 0;
	dining->all_ate = 0;
	dining->is_alive = IS_ALIVE;
}

int	main(int argc, char *argv[])
{
	t_dining dining;
	
	memset((void *)&dining, 0, sizeof(dining));
	init_dining(&dining);
	if (argc != 5 && argc != 6)
		return (arguments_error(argc, argv), -1);
	if (handle_arguments(argc, argv, &dining) == -1)
		return (arguments_error(argc, argv), -1);
	launch_dining_philosopher(&dining);
	
	test_handle_arguments(&dining);
	return (0);
}