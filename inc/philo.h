#ifndef PHILO_H
# define PHILO_H

# define SUPERVISOR_USLEEP	2000 // Limits how often supervisor checks on philos

# define EDEFAULT	"Unknown error"
# define EMALLOC	"Malloc error"
# define EARGS		"Arguments have to be unsigned integers"
# define EPHILNUM	"Need at least 1 philosopher"

# define PHILO_ERR_MALLOC	"Malloc failure, aborting all processes\n"
# define PHILO_ERR_SEM		"Sem creation failure, aborting all processes\n"

# define PHILO_LOCAL_SEM_NAME	"philo_sem_"

// TODO Remove libft eventually and bake functions into program
# include "libft.h"		// ft_atox, ft_free, ft_time_sub, ft_time_add
# include <stdio.h>		// printf
# include <pthread.h>	// pthread
# include <sys/time.h>	// gettimeofday
# include <stdbool.h>	// bool
# include <errno.h>		// errno
# include <string.h>	// strerror

//	Semaphore philosophers
//
// Main thread
// 1. 
// 2.
// 3.
// 4.
// 5. fork() in a while
// 6. Create 2 threads to help supervise
// 6. sem_wait() for ready_sem
// 7. sem_post() for start_sem in a while
// 8. Supervise sim
//		- In a while(1), just check for dead_philo and stuffed_philos bools
// 9. End sim
//		- Post global stop sem
//		- waitpid() in a while
//
//	Supervisor help thread #1
// Monitors for global death sem that signals a philo has died.
// Any philo died = stop;
//
//	Supervisor help thread #2
// Monitors for global stuffed sem that signals philos are stuffed.
// All philos stuffed = stop.
//
// Philo thread
//
//


// ================================ SEMAPHORES =================================
typedef struct s_sem
{
	sem_t	*forks;
	sem_t	*print;
}	t_sem;

// =================================== RULES ===================================
typedef struct s_rules
{
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	meals_to_end;
}	t_rules;

// =================================== TIME ====================================
typedef struct s_time
{
	struct timeval	start;
	struct timeval	current;
}	t_time;

// ================================ MAIN STRUCT ================================
typedef struct s_main
{
	unsigned int	num_philos;
	t_rules			rules;
	t_time			time;
	t_global_sem	global_sem;
}	t_main;

// =============================== PHILO STRUCT ================================
typedef struct s_philo
{
	int				id;
	t_rules			rules;
	t_time			time;
	t_philo_sem		sem;
}	t_philo;

// ============================= SUPERVISOR STRUCT =============================
typedef struct s_supervisor
{
	unsigned int		num_philos;
	t_time				time;
	t_supervisor_sem	sem;
}	t_supervisor;

// init_exit.c
void	init_prog(t_prog *d);
void	exit_prog(t_prog *d, int exitval);
void	print_usage(void);
void	error_out(t_prog *d, char *err_str);

// parse_args.c
void	parse_args(t_prog *d, char **av);

// prepare_sim.c
void	prepare_sim(t_prog *d);
// end_sim.c
void	end_sim(t_prog *d);

// philo.c
bool	p_think(t_philo *d);
bool	p_eat(t_philo *d);
bool	p_sleep(t_philo *d);
void	*philo_thread(void *p);

// supervise_sim.c
void	supervise_sim(t_prog *d);

#endif
