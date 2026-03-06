/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_main_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:13:58 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/05 16:00:47 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*stuffed_watcher_thread(void *p)
{
	t_prog			*d;
	unsigned int	i;
	bool			stop;

	d = p;
	i = 0;
	stop = false;
	while (!stop && i < d->rules.num_philos)
	{
		sem_wait(d->sem.global.stuffed);
		sem_wait(d->sem.global.print);
		stop = d->stop;
		sem_post(d->sem.global.print);
		i++;
	}
	sem_wait(d->sem.global.print);
	if (d->stop)
	{
		sem_post(d->sem.global.print);
		return (NULL);
	}
	signal_stop(d);
	wait_stop_received(d);
	sem_post(d->sem.global.print);
	return (NULL);
}

static void	create_thread(t_prog *d)
{
	if (pthread_create(&d->threads.parent_stuffed_watcher.thread, NULL,
			stuffed_watcher_thread, d))
		error_stop_parent(d, ETHREAD);
	d->threads.parent_stuffed_watcher.is_created = true;
}

static void	wait_ready(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->rules.num_philos)
	{
		sem_wait(d->sem.global.ready);
		i++;
	}
}

static void	delay_start(t_prog *d)
{
	int	time_to_wait;

	gettimeofday(&d->time.current, NULL);
	time_to_wait = ft_time_sub(d->time.start, d->time.current);
	if (time_to_wait > 0)
		usleep(time_to_wait);
}

void	main_routine(t_prog *d)
{
	create_thread(d);
	delay_start(d);
	wait_ready(d);
	signal_start(d);
	sem_wait(d->sem.global.stop);
	d->stop = true;
	sem_post(d->sem.global.stop_received);
	sem_post(d->sem.global.stuffed);
	sem_post(d->sem.global.forks);
}
