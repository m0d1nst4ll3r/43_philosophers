#ifndef PHILO_H
# define PHILO_H

# define SUPERVISOR_USLEEP	2000 // Limits how often supervisor checks on philos

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
# include <pthread.h>	// pthread
# include <sys/time.h>	// gettimeofday
# include <stdbool.h>	// bool
# include <errno.h>		// errno
# include <string.h>	// strerror

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
	t_sem	*forks;
	t_sem	*print;
	t_sem	*start;
	t_sem	*death;
	t_sem	*stop;
	t_sem	*error;
	t_sem	**stuffed;
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
	struct timeval	start;
	struct timeval	current;
}	t_time;

// ================================ MAIN STRUCT ================================
typedef struct s_prog
{
	bool			is_parent;
	int				philo_id;
	pid_t			*philo_pids;
	t_rules			rules;
	t_time			time;
	t_sem			sem;
}	t_prog;

// init.c

// error.c

// exit.c

// philo.c

// supervisor.c

// fork.c

// args.c



#endif
