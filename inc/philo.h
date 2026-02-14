/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:58:24 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/14 16:08:21 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define DEFAULT_ERR	"Unknown error"
# define ERR_MAL		"Malloc error"
# define ERR_TIME		"gettimeofday error"
# define ERR_ARG		"Arguments have to be unsigned integers"

// Libft
# include "libft.h" // TODO Remove libft eventually and bake functions into program
// Printf
# include <stdio.h>
// Pthread
# include <pthread.h>
// Time
# include <sys/time.h>
// Bool
# include <stdbool.h>
// Errno/strerror
# include <errno.h>
# include <string.h>

// Time values expressed in ms
typedef struct s_time
{
	unsigned int	die;
	unsigned int	eat;
	unsigned int	sleep;
	unsigned int	eat_limit;
	bool			is_eat_limit_set;
	struct timeval	current;
}	t_time;

typedef struct s_philo
{
	int		id;
	char	fork;
}	t_philo;

//	God struct
// num_philo		number of philosophers read from args
// time				time-related values including current time
// philosophers		array of philosophers (and their forks),
//					malloc'd in parse_args
typedef struct s_prog
{
	unsigned int	num_philo;
	t_time			time;
	t_philo			*philo;
}	t_prog;

// init_exit.c
void	init_prog(t_prog *d);
void	exit_prog(t_prog *d, int exitval);
void	print_usage(void);
void	error_out(t_prog *d, char *err_str);

// args.c
void	parse_args(t_prog *d, char **av);

#endif
