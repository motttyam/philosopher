/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:56:16 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/09/07 15:39:34 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef enum
{
	DIRTY = 0,
	CLEAN
}					fork_state;

typedef enum
{
	NO,
	YES
}					all_ate;

typedef enum
{
	IS_ALIVE = 0,
	IS_DEATH
}					death_flag;

typedef struct s_fork
{
	int				fork_id;
	int				fork_state;
	pthread_mutex_t	lock;
}					t_fork;

typedef struct s_philo
{
	void			*ptr_dining;
	t_fork			*l_fork;
	t_fork 			*r_fork;
	pthread_t		th;
	int				philo_id;
	int				eaten_count;
	int				is_alive;
}					t_philo;

typedef struct s_dining
{
	t_philo			*philos;
	t_fork			*forks;
	struct timeval	tv;
	long			start_time;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				all_ate;
	int				is_alive;
}					t_dining;

// init_dining
void				init_dining(t_dining *dining);
int					init_forks(t_dining *dining);
int					init_philosophers(t_dining *dining);

// dining_philosopher
void				*th_philosopher(void *philo);
void				launch_dining_philosopher(t_dining *dining);

// error
int					arguments_error(int argc, char **argv);

// utils
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *s);
int					ft_isdigit(int c);
int					ft_strdigit(char *str);

// test
void				test_handle_arguments(t_dining *dining);
void				print_dining(t_dining *dining);

#endif