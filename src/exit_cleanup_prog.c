/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cleanup_prog.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:05:11 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/02 15:17:39 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_pids(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->rules.num_philos)
	{
		if (d->philo_pids[i] > 0)
			waitpid(d->philo_pids[i], NULL, 0);
		i++;
	}
}

static void	join_threads(t_prog *d)
{
	if (d->threads.parent_stuffed_watcher.is_created)
		pthread_join(d->threads.parent_stuffed_watcher.thread, NULL);
	if (d->threads.philo_death_watcher.is_created)
		pthread_join(d->threads.philo_death_watcher.thread, NULL);
	if (d->threads.philo_stop_watcher.is_created)
		pthread_join(d->threads.philo_stop_watcher.thread, NULL);
}

static void	close_sems(t_prog *d)
{
	if (d->sem.global.forks != SEM_FAILED)
		sem_close(d->sem.global.forks);
	if (d->sem.global.print != SEM_FAILED)
		sem_close(d->sem.global.print);
	if (d->sem.global.start != SEM_FAILED)
		sem_close(d->sem.global.start);
	if (d->sem.global.ready != SEM_FAILED)
		sem_close(d->sem.global.ready);
	if (d->sem.global.stop != SEM_FAILED)
		sem_close(d->sem.global.stop);
	if (d->sem.global.stop_received != SEM_FAILED)
		sem_close(d->sem.global.stop_received);
	if (d->sem.global.stuffed != SEM_FAILED)
		sem_close(d->sem.global.stuffed);
	if (d->sem.philo.death_value != SEM_FAILED)
		sem_close(d->sem.philo.death_value);
}

static void	free_mallocs(t_prog *d)
{
	free(d->philo_pids);
}

void	cleanup_prog(t_prog *d)
{
	if (d->is_parent && d->philo_pids)
		wait_pids(d);
	join_threads(d);
	close_sems(d);
	free_mallocs(d);
}
