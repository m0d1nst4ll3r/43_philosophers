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


// ============================== THREAD STRUCTS ===============================
typedef struct s_philo_stop_monitor
{
	sem_t	*global_stop_sem;
	sem_t	*local_stop_var_sem;
	bool	*local_stop;
}	t_philo_stop_monitor;

typedef struct s_supervisor_death_monitor
{
	sem_t	*local_death_var_sem;
	sem_t	*global_death_sem;
	bool	*is_philo_dead;
}	t_supervisor_death_monitor;

typedef struct s_supervisor_stuffed_monitor
{
	sem_t	*local_stuffed_var_sem;
	sem_t	*global_stuffed_sem;
	bool	*are_philos_stuffed;
	int		num_philos;
}	t_supervisor_stuffed_monitor;

// ================================ SEMAPHORES =================================
typedef struct s_sem_supervisor
{
	sem_t	*dead_var;
	sem_t	*stuffed_var;
}	t_sem_supervisor;

typedef struct s_sem_philo
{
	sem_t	*stop_var;
}	t_sem_philo;

typedef struct s_sem_global
{
	sem_t	*forks;
	sem_t	*print;
	sem_t	*ready;
	sem_t	*start;
	sem_t	*stop;
	sem_t	*dead;
	sem_t	*stuffed;
	sem_t	*critical_error;
}	t_sem_global;

typedef struct s_sem;
{
	t_sem_global		global;
	t_sem_philo			philo;
	t_sem_supervisor	supervisor;
}	t_sem;

// ============================== THREAD OBJECTS ===============================
typedef struct s_thread_philo
{
	pthread_t	stop_monitor;
}	t_thread_philo;

typedef struct s_thread_supervisor
{
	pthread_t	death_monitor;
	pthread_t	stuffed_monitor;
}	t_thread_supervisor;

typedef struct s_thread
{
	t_thread_supervisor	supervisor;
	t_thread_philo		philo;
}	t_thread;

// =================================== TIME ====================================
typedef struct s_time
{
	unsigned int	to_die;
	unsigned int	to_eat;
	unsigned int	to_sleep;
	unsigned int	meals_to_end;
	struct timeval	start;
	struct timeval	current;
}	t_time;

// ================================ MAIN STRUCT ================================
typedef struct s_prog
{
	unsigned int	num_philos;
	int				philo_id;
	t_time			time;
	t_sem			sem;
	t_thread		thread;
}	t_prog;

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
