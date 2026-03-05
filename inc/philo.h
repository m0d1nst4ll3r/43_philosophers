/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:58:24 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/05 10:57:56 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define SUPERVISOR_USLEEP	1000 // Limits how often supervisor checks on philos

# define EDEFAULT	"Unknown error"
# define EMALLOC	"Malloc error"
# define ETHREAD	"Failed creating thread"
# define EMUTEX		"Failed creating mutex"

// TODO Remove libft eventually and bake functions into program
# include "philo_util.h"	// ft_time_sub, ft_time_add, ft_atox
# include <pthread.h>		// pthread
# include <stdlib.h>		// malloc, free, exit
# include <unistd.h>		// usleep, write
# include <sys/time.h>		// gettimeofday
# include <stdbool.h>		// bool
# include <string.h>		// memset
# include <stdio.h>			// printf

// =================================== RULES ===================================
typedef struct s_rules
{
	unsigned int	num_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	meals_to_end;
}	t_rules;

// =============================== THREAD/MUTEX ================================

typedef struct s_thread
{
	pthread_t	obj;
	bool		created;
}	t_thread;

typedef struct s_mutex
{
	pthread_mutex_t	obj;
	bool			created;
}	t_mutex;

// =============================== PHILO STRUCT ================================
typedef struct s_philo_mutex
{
	t_mutex			lfork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*stuffed_philos;
	t_mutex			death_time;
}	t_philo_mutex;

typedef struct s_philo_time
{
	unsigned int	meals_eaten;
	unsigned int	*stuffed_philos;
	const bool		*is_end_of_sim;
	struct timeval	current;
	struct timeval	death;
	struct timeval	start;
}	t_philo_time;

typedef struct s_philo
{
	int				id;
	t_thread		thread;
	t_philo_mutex	mutex;
	t_philo_time	time;
	t_rules			rules;
}	t_philo;

// ================================ MAIN STRUCT ================================
typedef struct s_main_time
{
	unsigned int	stuffed_philos;
	struct timeval	start;
	struct timeval	current;
	bool			is_end_of_sim;
}	t_main_time;

typedef struct s_main_mutex
{
	t_mutex	print;
	t_mutex	stuffed_philos;
}	t_main_mutex;

typedef struct s_prog
{
	t_philo			*philos;
	t_main_time		time;
	t_main_mutex	mutex;
	t_rules			rules;
}	t_prog;

// Called from main
bool			init_args(t_prog *d, char **av);
void			prepare_sim(t_prog *d);

// Philo routine
void			*philo_thread(void *p);
bool			p_eat(t_philo *d);

// Supervisor
void			supervise_sim(t_prog *d);

// Exit
void			error_out(t_prog *d, char *err_str);
void			cleanup_prog(t_prog *d);

// Util functions defined in philo_util.h

#endif
