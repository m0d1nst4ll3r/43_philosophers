/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_sim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 21:58:42 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/03 12:32:05 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philos(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->rules.num_philos)
	{
		d->philos[i].id = i;
		if (!i)
			d->philos[i].mutex.rfork
				= &d->philos[d->rules.num_philos - 1].mutex.lfork.obj;
		else
			d->philos[i].mutex.rfork = &d->philos[i - 1].mutex.lfork.obj;
		d->philos[i].mutex.stuffed_philos = &d->mutex.stuffed_philos.obj;
		d->philos[i].mutex.print = &d->mutex.print.obj;
		d->philos[i].rules = d->rules;
		d->philos[i].time.stuffed_philos = &d->time.stuffed_philos;
		d->philos[i].time.is_end_of_sim = &d->time.is_end_of_sim;
		i++;
	}
}

static void	create_mutexes(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->rules.num_philos)
	{
		if (pthread_mutex_init(&d->philos[i].mutex.lfork.obj, NULL))
			error_out(d, EMUTEX);
		d->philos[i].mutex.lfork.created = true;
		if (pthread_mutex_init(&d->philos[i].mutex.death_time.obj, NULL))
			error_out(d, EMUTEX);
		d->philos[i].mutex.death_time.created = true;
		i++;
	}
	if (pthread_mutex_init(&d->mutex.print.obj, NULL))
		error_out(d, EMUTEX);
	d->mutex.print.created = true;
	if (pthread_mutex_init(&d->mutex.stuffed_philos.obj, NULL))
		error_out(d, EMUTEX);
	d->mutex.stuffed_philos.created = true;
}

static void	create_threads(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->rules.num_philos)
	{
		if (pthread_create(&d->philos[i].thread.obj, NULL,
				philo_thread, d->philos + i))
		{
			d->time.is_end_of_sim = true;
			pthread_mutex_unlock(&d->mutex.print.obj);
			error_out(d, ETHREAD);
		}
		d->philos[i].thread.created = true;
		i++;
	}
}

static void	init_time(t_prog *d)
{
	unsigned int	i;
	struct timeval	death_time;

	gettimeofday(&d->time.start, NULL);
	death_time = ft_time_add(d->time.start, d->rules.time_to_die);
	i = 0;
	while (i < d->rules.num_philos)
	{
		d->philos[i].time.start = d->time.start;
		d->philos[i].time.death = death_time;
		i++;
	}
}

void	prepare_sim(t_prog *d)
{
	d->philos = malloc(sizeof(*d->philos) * d->rules.num_philos);
	if (!d->philos)
		error_out(d, EMALLOC);
	memset(d->philos, 0, sizeof(*d->philos) * d->rules.num_philos);
	init_philos(d);
	create_mutexes(d);
	pthread_mutex_lock(&d->mutex.print.obj);
	create_threads(d);
	init_time(d);
	pthread_mutex_unlock(&d->mutex.print.obj);
}
