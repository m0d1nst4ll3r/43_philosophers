#ifndef PHILO_H
# define PHILO_H

# define SUPERVISOR_USLEEP	2000 // Limits how often supervisor checks on philos

# define EDEFAULT	"Unknown error"
# define EMALLOC	"Malloc error"
# define EARGS		"Arguments have to be unsigned integers"
# define EPHILNUM	"Need at least 1 philosopher"
# define ESEM		"Error creating semaphore"
# define ESEMAVAIL	"Some semaphores already exist with no permissions"

# define PHILO_ERR_MALLOC	"Malloc failure, aborting all processes\n"
# define PHILO_ERR_SEM		"Sem creation failure, aborting all processes\n"

# define SEM_NAME_FORKS		"philo_sem_forks"
# define SEM_NAME_PRINT		"philo_sem_print"

# define SEM_NAME_START		"philo_sem_start"
# define SEM_NAME_DEAD		"philo_sem_dead"
# define SEM_NAME_STOP		"philo_sem_stop"
# define SEM_NAME_ERROR		"philo_sem_error"

# define SEM_NAME_STUFFED	"philo_sem_stuffed_"

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
	sem_t	*forks;
	sem_t	*print;
	char	**stuffed;
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
typedef struct s_prog
{
	unsigned int	num_philos;
	int				philo_id;
	pid_t			*children_pids;
	t_rules			rules;
	t_time			time;
	t_sem			sem;
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
