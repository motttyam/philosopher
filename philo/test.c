/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:02:06 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/09/05 22:36:46 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	test_handle_arguments(t_dining *dining)
{
	printf("num_philos: %d\n", dining->num_of_philos);
	printf("die: %d\n", dining->time_to_die);
	printf("eat: %d\n", dining->time_to_eat);
	printf("sleep: %d\n", dining->time_to_sleep);
	printf("must_eat: %d\n", dining->must_eat);
	return ;
}

void	print_fork(t_fork *fork)
{
	printf("Fork id: %d\n", fork->fork_id);
	printf("Owner id: %d\n", fork->owner_id);
	printf("Fork state: %d\n", fork->fork_state);
}

void	print_philo(t_philo *philo)
{
	printf("Philo id: %d\n", philo->philo_id);
	printf("Left fork: %p\n", (void *)philo->l_fork);
	printf("Right fork: %p\n", (void *)philo->r_fork);
	printf("Eaten count: %d\n", philo->eaten_count);
	printf("Is alive: %d\n", philo->is_alive);
}

void	print_dining(t_dining *dining)
{
	printf("Number of philosophers: %d\n", dining->num_of_philos);
	printf("Time to die: %d\n", dining->time_to_die);
	printf("Time to eat: %d\n", dining->time_to_eat);
	printf("Time to sleep: %d\n", dining->time_to_sleep);
	printf("Must eat: %d\n", dining->must_eat);
	printf("All ate: %d\n", dining->all_ate);
	printf("All alive: %d\n", dining->is_alive);

	printf("\nForks:\n");
	for (int i = 0; i < dining->num_of_philos; i++)
	{
		print_fork(&dining->forks[i]);
	}

	printf("\nPhilosophers:\n");
	for (int i = 0; i < dining->num_of_philos; i++)
	{
		print_philo(&dining->philos[i]);
	}
}