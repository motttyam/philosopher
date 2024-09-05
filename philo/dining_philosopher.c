/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_philosopher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:08:16 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/09/05 10:46:28 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_philosophers(t_dining *dining)
{
    int i;
    
    i = 0;
    if(dining->num_of_philos >= 200)
        return (arguments_error(0, NULL), test_handle_arguments(dining), -1);
    dining->philos = (t_dining *)malloc(sizeof(t_dining) * dining->num_of_forks);
    if (dining->philos == NULL)
        return (-1);
    // zj
    while (i < dining->num_of_philos)
    {
        pthread_create()
    }
}


void launch_dining_philosopher(t_dining *dining)
{
    init_forks(dining);
    init_philosophers(dining);
}