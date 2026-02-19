/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:06:55 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/19 17:21:33 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutexes(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->num_philos)
	{
		pthread_mutex_destroy(&d->philos[i].mutex.lfork);
		pthread_mutex_destroy(&d->philos[i].mutex.death_time);
		i++;
	}
	pthread_mutex_destroy(&d->mutex.print);
	pthread_mutex_destroy(&d->mutex.stuffed_philos);
}

void	init_prog(t_prog *d)
{
	d->philos = NULL;
}

void	exit_prog(t_prog *d, int exitval)
{
	destroy_mutexes(d);
	ft_free((void *)&d->philos);
	exit(exitval);
}

void	print_usage(void)
{
	printf("./philo number_of_philosophers time_to_die time_to_eat time_to_sleep\
 [number_of_times_each_philosopher_must_eat]\n");
	exit(0);
}

void	error_out(t_prog *d, char *err_str)
{
	if (!err_str)
		err_str = EDEFAULT;
	write(2, "philo: ", 7);
	write(2, err_str, sizeof(err_str) - 1);
	write(2, "\n", 1);
	exit_prog(d, 1);
}
