/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_main_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:13:58 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/02 13:46:26 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*stuffed_watcher_thread(void *p)
{
	t_prog	*d
	int		i;

	d = p;
	i = 0;
	while (i < d->rules.num_philos)
	{
		if (d->stop)
			break ;
		sem_wait(d->sem.global.stuffed);
		i++;
	}
	sem_wait(d->sem.global.print);
	if (d->stop)
	{
		sem_post(d->sem.global.print);
		return (NULL);
	}
	post_stop_loop(d->sem.global.stop);
	wait_stop_received(d->sem.global.stop);
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

void	main_routine(t_prog *d)
{
	create_thread(d);
	wait_ready(d);
	signal_start(d);
	sem_wait(d->sem.global.stop);
	d->stop = true;
	sem_post(d->global.stuffed);
	pthread_join(d->threads.parent_stuffed_watcher);
}
