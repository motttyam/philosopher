/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:47:26 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/10/19 19:47:39 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int handle_arguments(int argc, char **argv, t_dining *dining)
{
	if(ft_strdigit(argv[1]) == 1 && ft_strdigit(argv[2]) == 1 
		&& ft_strdigit(argv[3]) == 1 && ft_strdigit(argv[4]) == 1)
	{
		dining->num_of_philos = ft_atoi(argv[1]);
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