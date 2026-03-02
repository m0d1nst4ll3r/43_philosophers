/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:06:55 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/02 11:51:52 by rapohlen         ###   ########.fr       */
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

void	exit_prog(t_prog *d, int exitval)
{
	destroy_mutexes(d);
	ft_free((void *)&d->philos);
	exit(exitval);
}

// This should be fprintf (or my own ft_fprintf) and it should use errno
// But this project doesn't allow fprintf/libft/errno, because 42 is dumb
static void	puterr(char *err_str)
{
	unsigned int	i;

	if (!err_str)
		err_str = EDEFAULT;
	i = 0;
	while (err_str[i])
		i++;
	write(2, "philo: ", 7);
	write(2, err_str, i);
	write(2, "\n", 1);
}

void	error_out(t_prog *d, char *err_str)
{
	puterr(err_str);
	exit_prog(d, 1);
}
