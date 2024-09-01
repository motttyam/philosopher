/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:56:16 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/09/01 21:48:01 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef enum
{
	DIRTY,
	CLEAN
}					fork_state;

typedef enum
{
	YES,
	NO
}					all_ate;

typedef enum
{
	IS_ALIVE,
	IS_DEATH
}					death_flag;

typedef struct s_fork
{
	int				fork_id;
	int				owner_id;
	int				fork_state;
	pthread_mutex_t	lock;
}					t_fork;

typedef struct s_philo
{
	int				philo_id;
	t_fork			*l_fork;
	t_fork			*r_fork;
	pthread_t		th;
	int				eaten_count;
	int				is_alive;
}					t_philo;

typedef struct s_dining
{
	t_philo			*philos;
	t_fork			*forks;
	int				num_of_philos;
	int				num_of_forks;
	int				eating_time;
	int				sleeping_time;
	int				must_eat;
	int				all_ate;
	int				is_alive;
}	t_dining;

int	arguments_error(void);

#endif