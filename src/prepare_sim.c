/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_sim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 21:58:42 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/16 06:25:40 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philos(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->num_philos)
	{
		d->philos[i].id = i;
		if (!i)
			d->philos[i].mutex.rfork
				= &d->philos[d->num_philos - 1].mutex.lfork;
		else
			d->philos[i].mutex.rfork = &d->philos[i - 1].mutex.lfork;
		d->philos[i].mutex.stuffed_philos = &d->mutex.stuffed_philos;
		d->philos[i].mutex.is_end_of_sim = &d->mutex.is_end_of_sim;
		d->philos[i].mutex.print = &d->mutex.print;
		d->philos[i].time.to_die = d->time.to_die;
		d->philos[i].time.to_eat = d->time.to_eat;
		d->philos[i].time.to_sleep = d->time.to_sleep;
		d->philos[i].time.meals_to_end = d->time.meals_to_end;
		d->philos[i].time.meals_eaten = 0;
		d->philos[i].time.stuffed_philos = &d->time.stuffed_philos;
		d->philos[i].time.is_end_of_sim = &d->time.is_end_of_sim;
		i++;
	}
}

static void	create_mutexes(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->num_philos)
	{
		pthread_mutex_init(&d->philos[i].mutex.lfork, NULL);
		pthread_mutex_init(&d->philos[i].mutex.death_time, NULL);
		i++;
	}
	pthread_mutex_init(&d->mutex.print, NULL);
	pthread_mutex_init(&d->mutex.is_end_of_sim, NULL);
	pthread_mutex_init(&d->mutex.stuffed_philos, NULL);
}

static void	create_threads(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->num_philos)
	{
		pthread_create(&d->philos[i].thread, NULL, philo_thread, d->philos + i);
		i++;
	}
}

static void	init_time(t_prog *d)
{
	unsigned int	i;
	struct timeval	death_time;

	gettimeofday(&d->time.start, NULL);
	death_time = ft_time_add(d->time.start, d->time.to_die * 1000);
	i = 0;
	while (i < d->num_philos)
	{
		d->philos[i].time.start = d->time.start;
		d->philos[i].time.death = death_time;
		i++;
	}
}

// Does malloc, prepares all philo structs
void	prepare_sim(t_prog *d)
{
	d->time.is_end_of_sim = false;
	d->time.stuffed_philos = 0;
	d->philos = malloc(sizeof(*d->philos) * d->num_philos);
	if (!d->philos)
		error_out(d, EMALLOC);
	init_philos(d);
	create_mutexes(d);
	pthread_mutex_lock(&d->mutex.print);
	create_threads(d);
	init_time(d);
	pthread_mutex_unlock(&d->mutex.print);
}
