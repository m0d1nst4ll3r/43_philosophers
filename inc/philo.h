/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:38:49 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/19 20:38:52 by rapohlen         ###   ########.fr       */
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
typedef struct s_sem
{
	sem_t	*ref;
	char	*name;
}	t_sem;

typedef struct s_sem_stuffed
{
	sem_t	*ref;
	char	*name;
	bool	is_stuffed;
}	t_sem_stuffed;

//	These semaphores are used in a normal way:
// forks, print
//	These semaphores are used as signals:
// start, death, stop, error, stuffed[]
//	They are kept uncreated until signal needs to be sent.
typedef struct s_sem_list
{
	t_sem			forks;
	t_sem			print;
	t_sem			start;
	t_sem			death;
	t_sem			stop;
	t_sem_stuffed	*stuffed;
}	t_sem_list;

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

// ================================ MAIN STRUCT ================================
typedef struct s_prog
{
	bool			is_parent;
	unsigned int	philo_id;
	pid_t			*philo_pids;
	t_rules			rules;
	t_time			time;
	t_sem_list		sem;
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
