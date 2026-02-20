/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:13:58 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/20 14:54:45 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	signal_start(t_prog *d)
{
	d->sem.start.ref = create_sem(d->sem.start.name, 0);
	if (d->sem.start.ref == SEM_FAILED)
		error_stop(d, ESEM);
}

static void	signal_stop(t_prog *d)
{
	d->sem.stop.ref = create_sem(d->sem.stop.name, 0);
	if (d->sem.start.ref == SEM_FAILED)
		error_stop(d, ESTOP);
}

static unsigned int	count_stuffed(t_prog *d)
{
	unsigned int	i;
	unsigned int	stuffed_philos;

	i = 0;
	stuffed_philos = 0;
	while (i < d->rules.num_philos)
	{
		if (!d->sem.stuffed[i].is_stuffed)
			if (sem_exists(d->sem.stuffed[i].name))
				d->sem.stuffed[i].is_stuffed = true;
		if (d->sem.stuffed[i].is_stuffed)
			stuffed_philos++;
		i++;
	}
	return (stuffed_philos);
}

static void	supervisor_loop(t_prog *d)
{
	while (!sem_exists(d->sem.death.name)
		&& count_stuffed(d) != d->rules.num_philos)
		usleep(SUPERVISOR_USLEEP);
	signal_stop(d);
}

void	supervisor_routine(t_prog *d)
{
	signal_start(d);
	supervisor_loop(d);
}
