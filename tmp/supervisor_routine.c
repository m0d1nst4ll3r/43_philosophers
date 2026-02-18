/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:13:58 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/18 20:17:03 by rapohlen         ###   ########.fr       */
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
		error_out(d, ESTOP);
}

static int	count_stuffed(t_prog *d)
{
	int	i;
	int	stuffed_philos;

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
}

static void	supervisor_loop(t_prog *d)
{
	while (1)
	{
		if (sem_exists(d->sem.death.name))
		{
			sem_wait(d->sem.print.ref);
			printf("%d %d died\n");
			sem_post(d->sem.print.ref);
			break ;// Philo is dead: post stop and print death
		}
		if (count_stuffed(d) == d->rules.num_philos)
			break ;
	}
	signal_stop(d);
}

void	supervisor_routine(t_prog *d)
{
	signal_start(d);
	supervisor_loop(d);
}
