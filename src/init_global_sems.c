/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global_sems.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:45:45 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/02 11:02:21 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_global_sems(t_prog *d)
{
	d->sem.forks = create_sem(SEM_FORKS_NAME, d->rules.num_philos);
	d->sem.print = create_sem(SEM_PRINT_NAME, 1);
	d->sem.start = create_sem(SEM_START_NAME, 0);
	d->sem.ready = create_sem(SEM_READY_NAME, 0);
	d->sem.stop = create_sem(SEM_STOP_NAME, 0);
	d->sem.stop_received = create_sem(SEM_STOP_RECEIVED_NAME, 0);
	d->sem.stuffed = create_sem(SEM_STUFFED_NAME, 0);
	if (d->sem.forks == SEM_FAILED || d->sem.print == SEM_FAILED
		|| d->sem.start == SEM_FAILED || d->sem.ready == SEM_FAILED
		|| d->sem.stop == SEM_FAILED || d->sem.stop_received == SEM_FAILED
		|| d->sem.stuffed == SEM_FAILED)
		error_out(d, ESEM);
}
