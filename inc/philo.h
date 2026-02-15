/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:58:24 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/15 02:26:43 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define SUPERVISOR_USLEEP	1000 // Limits how often supervisor checks on philos

# define DEFAULT_ERR	"Unknown error"
# define ERR_MAL		"Malloc error"
# define ERR_TIME		"gettimeofday error"
# define ERR_ARG		"Arguments have to be unsigned integers"

// TODO Remove libft eventually and bake functions into program
# include "libft.h"		// ft_atox, ft_free, ft_time_diff
# include <stdio.h>		// printf
# include <pthread.h>	// pthread
# include <sys/time.h>	// gettimeofday
# include <stdbool.h>	// bool
# include <errno.h>		// errno
# include <string.h>	// strerror

//	Philosopher struct
// Exists in an array. Each element is passed to its corresponding philo thread.
// This is done so threads data is compartmentalized as per subject guidelines.
// Supervisor has access to everything but only reads values,
//	except for is_end_of_sim.
//
//	id				id used for printing and strategy
// mutex:
//	lfork			left fork
//	rfork			right fork
//	print			for printf
//	end				for is_end_of_sim
//	meals			for meals_eaten
//	death_time		for death time
// time:
//	to_die			value for calculating death time after starting eating
//	to_eat			value for usleep() after starting eating
//	to_sleep		value for usleep() after finished eating
//	meals_eaten		how many meals eaten
//	current			current time, compared with last_action
//	last_action		when last action started, used for printing
//					also used for keeping to sim schedule (if possible)
//	death			updates on eating, checked by supervisor to determine death
//	start			time when philosophers all started together (for printing)
//	is_end_of_sim	set by supervisor when it's time to quit
//
// Any address means the value is shared and not specific to this philosopher.
// Values shared between philos are only mutexes.
// Values tracked by supervisor are meals_eaten and death time.
// Value set by supervisor is is_end_of_sim.
// Start time is an address because it has to be updated after threads launch,
//	by the main program thread preparing the sim. It is shared with other
//	philos, but only read, thus no need for a mutex.
typedef struct s_philo_mutex
{
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*end;
	pthread_mutex_t	meals;
	pthread_mutex_t	death_time;
}	t_philo_mutex;

typedef struct s_philo_time
{
	unsigned int	to_die;
	unsigned int	to_eat;
	unsigned int	to_sleep;
	unsigned int	meals_eaten;
	struct timeval	current;
	struct timeval	last_action;
	struct timeval	death;
	struct timeval	*start;
	bool			*is_end_of_sim;
}	t_philo_time;

typedef struct s_philo
{
	int				id;
	t_philo_mutex	mutex;
	t_philo_time	time;
}	t_philo;

//	Program struct
//
//	num_philos		number of philosophers from params
//	threads			philo threads
// philos:
//	Philosophers array containing their data (see philosopher struct)
// time:
//	to_die			if a philo has not started eating for this long, it dies
//	to_eat			how long a philo holds forks after starting eating
//	to_sleep		how long a philo sleeps after finishing eating
//	meals_to_end	how many meals each philosopher has to eat to end the sim
//	start			when the simulation started
//	current			current time set and used by the supervisor
//	is_end_of_sim	set to true when philos have eaten enough or one dies
// mutex:
//	forks			forks distributed to philos (their lfork and rfork)
//	print			used for printf calls, philos and supervisor both use this
//	end				used for is_end_of_sim, supervisor writes, philos read
//
// Philo-specific mutexes for values tracked by the supervisor
//	(death time, meals_eaten) are found in the philos array.
typedef struct s_time
{
	unsigned int	to_die;
	unsigned int	to_eat;
	unsigned int	to_sleep;
	unsigned int	meals_to_end;
	struct timeval	start;
	struct timeval	current;
	bool			is_end_of_sim;
}	t_time;

typedef struct s_mutex
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	end;
}	t_mutex;

typedef struct s_prog
{
	unsigned int	num_philos;
	pthread_t		*threads;
	t_philo			*philos;
	t_time			time;
	t_mutex			mutex;
}	t_prog;

// init_exit.c
void	init_prog(t_prog *d);
void	exit_prog(t_prog *d, int exitval);
void	print_usage(void);
void	error_out(t_prog *d, char *err_str);

// args.c
void	parse_args(t_prog *d, char **av);

// prepare_sim.c
void	prepare_sim(t_prog *d);

#endif
