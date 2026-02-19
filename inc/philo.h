/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:58:24 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/19 17:20:21 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define SUPERVISOR_USLEEP	2000 // Limits how often supervisor checks on philos

# define BSIZE		31 // For custom printing

# define EDEFAULT	"Unknown error"
# define EMALLOC	"Malloc error"
# define EARGS		"Arguments have to be unsigned integers"
# define EPHILNUM	"Need at least 1 philosopher"

// TODO Remove libft eventually and bake functions into program
# include "libft.h"		// ft_atox, ft_free, ft_time_sub, ft_time_add
# include <pthread.h>	// pthread
# include <sys/time.h>	// gettimeofday
# include <stdbool.h>	// bool
# include <stdio.h>

typedef struct s_philo_mutex
{
	pthread_mutex_t	lfork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*stuffed_philos;
	pthread_mutex_t	death_time;
}	t_philo_mutex;

typedef struct s_philo_time
{
	unsigned int	to_die;
	unsigned int	to_eat;
	unsigned int	to_sleep;
	unsigned int	meals_to_end;
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
	pthread_t		thread;
	t_philo_mutex	mutex;
	t_philo_time	time;
}	t_philo;

typedef struct s_time
{
	unsigned int	to_die;
	unsigned int	to_eat;
	unsigned int	to_sleep;
	unsigned int	meals_to_end;
	unsigned int	stuffed_philos;
	struct timeval	start;
	struct timeval	current;
	bool			is_end_of_sim;
}	t_time;

typedef struct s_mutex
{
	pthread_mutex_t	print;
	pthread_mutex_t	stuffed_philos;
}	t_mutex;

typedef struct s_prog
{
	unsigned int	num_philos;
	t_philo			*philos;
	t_time			time;
	t_mutex			mutex;
}	t_prog;

// print_message.c
void	print_message(int time, int id, char *str);

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
