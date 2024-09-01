/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:58:32 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/09/01 21:47:44 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int handle_argument(int argc, char *argv[], t_dining dining)
{
	return (0);
}

int	main(int argc, char *argv[])
{
	t_dining dining;
	
	if (argc != 5 && argc != 6)
		return (arguments_error);
	if (handle_arguments(argc, argv, dining) == -1)
		return (arguments_error);
	// if (launch_philosopher())
	return (0);
}