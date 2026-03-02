/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:06:55 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/02 19:13:16 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutexes(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->rules.num_philos)
	{
		if (d->philos[i].mutex.lfork.created)
			pthread_mutex_destroy(&d->philos[i].mutex.lfork.obj);
		if (d->philos[i].mutex.death_time.created)
			pthread_mutex_destroy(&d->philos[i].mutex.death_time.obj);
		i++;
	}
	if (d->mutex.print.created)
		pthread_mutex_destroy(&d->mutex.print.obj);
	if (d->mutex.stuffed_philos.created)
		pthread_mutex_destroy(&d->mutex.stuffed_philos.obj);
}

static void	join_threads(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->rules.num_philos)
	{
		if (d->philos[i].thread.created)
			pthread_join(d->philos[i].thread.obj, NULL);
		i++;
	}
}

void	cleanup_prog(t_prog *d)
{
	join_threads(d);
	destroy_mutexes(d);
	ft_free((void *)&d->philos);
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
	cleanup_prog(d);
	exit(1);
}
