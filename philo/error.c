/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:03:30 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/11/03 23:18:34 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arguments_error(int argc, char **argv)
{
	int	i;

	printf("[WARNING]\n");
	printf("You should put the following 5 or 6 arguments on this program\n");
	printf("number_of_philosophers time_to_die time_to_eat time_to_sleep ");
	printf("(number_of_times_each_philosopher_must_eat)\n\n");
	printf("To meet the program's requirements, ");
	printf("where the first five arguments are mandatory ");
	printf("and the last one is optional \n");
	printf("[example] ./philo 5 800 200 200\n");
	printf("Your Input is\n");
	printf("some of arguments(at least one) are not valid\n");
	i = 0;
	while (i < argc)
	{
		printf("%s\n", argv[i]);
		i++;
	}
	return (-1);
}
