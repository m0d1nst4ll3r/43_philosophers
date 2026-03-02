/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:38:49 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/02 12:06:07 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define SUPERVISOR_USLEEP	1000 // Limits how often supervisor checks on philos

# define EDEFAULT	"Unknown error"
# define EMALLOC	"Malloc failure"
# define ESEM		"Failed creating semaphore"
# define EFORK		"Fork failure"
# define ETHREAD	"Failed creating thread"

# define SEM_FORKS_NAME			"philo_sem_forks"
# define SEM_PRINT_NAME			"philo_sem_print"
# define SEM_START_NAME			"philo_sem_start"
# define SEM_READY_NAME			"philo_sem_ready"
# define SEM_STOP_NAME			"philo_sem_stop"
# define SEM_STOP_RECEIVED_NAME	"philo_sem_stop_received"
# define SEM_STUFFED_NAME		"philo_sem_stuffed"
# define SEM_DEATH_VALUE_NAME	"philo_sem_death_value"

// TODO Remove libft eventually and bake functions into program
# include "libft.h"		// ft_atox, ft_free, ft_time_sub, ft_time_add
# include <stdio.h>		// printf
# include <stdbool.h>	// bool
# include <sys/time.h>	// gettimeofday
# include <sys/wait.h>	// waitpid
# include <fcntl.h>		// O_* constants
# include <semaphore.h>	// sem_open, sem_close, sem_unlink, sem_wait, sem_post

// ================================ SEMAPHORES =================================

typedef struct s_sem_global
{
	sem_t	*forks;
	sem_t	*print;
	sem_t	*start;
	sem_t	*ready;
	sem_t	*stop;
	sem_t	*stop_received;
	sem_t	*stuffed;
}	t_sem_global;

typedef struct s_sem_philo
{
	sem_t	*death_value;
}	t_sem_philo;

typedef struct s_sem
{
	t_sem_philo		philo;
	t_sem_global	global;
}	t_sem;

// =================================== RULES ===================================
typedef struct s_rules
{
	unsigned int	num_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	meals_to_end;
}	t_rules;

// =================================== TIME ====================================
typedef struct s_time
{
	unsigned int	meals_eaten;
	struct timeval	start;
	struct timeval	current;
	struct timeval	death;
}	t_time;

// ================================== THREADS ==================================

typedef struct s_thread
{
	pthread_t	thread;
	bool		is_created;
}	t_thread;

typedef struct s_threads
{
	t_thread	parent_stuffed_watcher;
	t_thread	philo_death_watcher;
	t_thread	philo_stop_watcher;
}	t_threads;

// ================================ MAIN STRUCT ================================
typedef struct s_prog
{
	bool			is_parent;
	bool			stop;
	unsigned int	philo_id;
	pid_t			*philo_pids;
	t_rules			rules;
	t_time			time;
	t_sem			sem;
	t_threads		threads;
}	t_prog;

// Called from main.c
bool	init_args(t_prog *d, char **av);
void	init_prog(t_prog *d);
void	init_malloc(t_prog *d);
void	init_sems(t_prog *d);
void	do_forks(t_prog *d);
void	cleanup_prog(t_prog *d);

// Called from do_forks.c
void	philo_routine(t_prog *d);
void	main_routine(t_prog *d);

// Called from philo_routine.c
void	init_philo_threads(t_prog *d);

// Called from philo_routine.c
bool	p_think(t_prog *d);
bool	p_eat(t_prog *d);
bool	p_sleep(t_prog *d);

// Util
bool	sem_exists(char *sem_name);
sem_t	*create_sem(char *sem_name, int value);

// Error
void	error_out(t_prog *d, char *err_str);
void	error_stop(t_prog *d, char *err_str);

#endif
