/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:02:06 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/09/05 10:02:14 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void test_handle_arguments(t_dining *dining)
{
	printf("num_philos: %d\n", dining->num_of_philos);
	printf("die: %d\n", dining->time_to_die);
	printf("eat: %d\n", dining->time_to_eat);
	printf("sleep: %d\n", dining->time_to_sleep);
	printf("must_eat: %d\n", dining->must_eat);
	return ;
}