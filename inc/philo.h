/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:38:49 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/20 20:28:09 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define SUPERVISOR_USLEEP	1000 // Limits how often supervisor checks on philos

# define EDEFAULT	"Unknown error"
# define EMALLOC	"Malloc failure"
# define ESEM		"Failed creating semaphore"
# define ESEMAVAIL	"A semaphore name is already in use by another process"
# define EFORK		"Fork failure"
# define ESTOP		"Critical: could not create stop sem, possibly after failed \
fork or other critical error"

# define SEM_NAME_PREFIX			"philo_sem_"
# define SEM_NAME_SUFFIX_FORKS		"_forks"
# define SEM_NAME_SUFFIX_PRINT		"_print"
# define SEM_NAME_SUFFIX_START		"_start"
# define SEM_NAME_SUFFIX_DEATH		"_death"
# define SEM_NAME_SUFFIX_STOP		"_stop"
# define SEM_NAME_SUFFIX_ERROR		"_error"
# define SEM_NAME_SUFFIX_STUFFED	"_stuffed"

// TODO Remove libft eventually and bake functions into program
# include "libft.h"		// ft_atox, ft_free, ft_time_sub, ft_time_add
# include <stdio.h>		// printf
# include <stdbool.h>	// bool
# include <errno.h>		// errno
# include <string.h>	// strerror
# include <sys/time.h>	// gettimeofday
# include <sys/wait.h>	// waitpid
# include <sys/types.h>	// kill
# include <signal.h>	// kill
# include <fcntl.h>		// O_* constants
# include <semaphore.h>	// sem_open, sem_close, sem_unlink, sem_wait, sem_post

// ================================ SEMAPHORES =================================

typedef struct s_sem_global
{
	sem_t	*forks;
	sem_t	*print;
	sem_t	*start;
	sem_t	*stop;
	sem_t	*stuffed;
}	t_sem_global;

typedef struct s_sem_philo
{
	sem_t	*stop_value;
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

typedef struct s_threads
{
	pthread_t	parent_stuffed_supervisor;
	pthread_t	philo_death_supervisor;
	pthread_t	philo_stop_supervisor;
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
void	init_sem_names(t_prog *d);
void	init_sem_refs(t_prog *d);
void	check_sems_avail(t_prog *d);
void	do_forks(t_prog *d);
void	cleanup_prog(t_prog *d);

// Called from do_forks.c
void	philo_routine(t_prog *d);
void	supervisor_routine(t_prog *d);

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
