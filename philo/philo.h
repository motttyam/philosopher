/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:56:16 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/11/16 18:29:03 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define SLEEP_INTERVAL 100
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef enum e_fork_state
{
	DIRTY = 0,
	CLEAN
}					t_fork_state;

typedef enum e_ate_state
{
	NOT_ATE = 0,
	ATE
}					t_ate_state;

typedef enum e_death_state
{
	IS_ALIVE = 0,
	IS_DEAD = 1,
}					t_death_state;

typedef enum e_think_state
{
	NOT_THINK = 0,
	THINKING,
}					t_think_state;

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
	t_fork			*r_fork;
	pthread_t		th;
	int				philo_id;
	long			meal_timelog;
	int				think_flag;
	int				eaten_count;
	int				is_alive;
	pthread_mutex_t	alive_lock;
	pthread_mutex_t	eaten_count_lock;
	pthread_mutex_t	meal_timelog_lock;
}					t_philo;

typedef struct s_dining
{
	t_philo			*philos;
	t_fork			*forks;
	long			start_time;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				all_ate;
	int				is_alive;
	pthread_mutex_t	alive_lock;
	pthread_mutex_t	all_ate_lock;
	pthread_mutex_t	printf_lock;
}					t_dining;

// main
void				launch_dining_philosopher(t_dining *dining);
void				*th_philosopher(void *philo);

// handling
int					handle_arguments(int argc, char **argv, t_dining *dining);
int					handle_dining_conditions(t_dining *dining);

// init_dining
void				init_dining(t_dining *dining);
int					init_forks(t_dining *dining);
int					init_philosophers(t_dining *dining);
void				init_each_philosopher(t_dining *dining, int *i);

// philosopher
int					take_forks(t_philo *philo);
int					take_a_fork(t_philo *philo, t_fork *fork);
int					think(t_philo *philo);
int					eat(t_philo *philo);
int					ft_sleep(t_philo *philo);

// monitoring
void				monitor_philosophers(t_dining *dining);
int					monitor_philosopher_death_state(t_dining *dining,
						t_philo *philo);
int					monitor_philosopher_eat_state(t_dining *dining, int ate);

// error
int					arguments_error(int argc, char **argv);

// utils
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *s);
int					ft_isdigit(int c);
int					ft_strdigit(char *str);

long				timestamp(t_philo *philo);
void				precise_usleep(int time, t_philo *philo);
int					validate_death_state(t_philo *philo);
void				print_log(char *str, t_philo *philo);

// test
void				test_handle_arguments(t_dining *dining);
void				print_dining(t_dining *dining);

#endif