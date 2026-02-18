/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_prog.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:05:11 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/18 19:08:49 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup_sem_refs(t_prog *d)
{
	int	i;

	if (d->sem.forks.ref != SEM_FAILED)
		sem_close(d->sem.forks.ref);
	if (d->sem.print.ref != SEM_FAILED)
		sem_close(d->sem.print.ref);
	if (d->sem.start.ref != SEM_FAILED)
		sem_close(d->sem.start.ref);
	if (d->sem.death.ref != SEM_FAILED)
		sem_close(d->sem.death.ref);
	if (d->sem.stop.ref != SEM_FAILED)
		sem_close(d->sem.stop.ref);
	if (d->sem.error.ref != SEM_FAILED)
		sem_close(d->sem.error.ref);
	i = 0
	while (i < d->rules.num_philos)
	{
		if (d->sem.stuffed[i].ref != SEM_FAILED)
			sem_close(d->sem.stuffed[i].ref);
		i++;
	}
}

static void	cleanup_sem_names(t_prog *d)
{
	int	i;

	free(d->sem.forks.name);
	free(d->sem.print.name);
	free(d->sem.start.name);
	free(d->sem.death.name);
	free(d->sem.stop.name);
	free(d->sem.error.name);
	i = 0;
	while (i < d->rules.num_philos)
	{
		free(d->sem.stuffed[i].name);
		i++;
	}
}

static void	cleanup_malloc(t_prog *d)
{
	free(d->philo_pids);
	free(d->sem.stuffed);
}

static void	wait_pids(t_prog *d)
{
	int	i;

	i = 0;
	while (i < d->rules.num_philos)
	{
		if (d->philo_pids[i] > 0)
			waitpid(d->philo_pids[i], NULL, 0);
		i++;
	}
}

void	cleanup_prog(t_prog *d)
{
	if (d->is_parent)
		wait_pids(d);
	cleanup_sem_refs(d);
	cleanup_sem_names(d);
	cleanup_malloc(d);
}
