/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global_sems.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:45:45 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/02 14:48:58 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_global_sems(t_prog *d)
{
	d->sem.global.forks = create_sem(SEM_FORKS_NAME, d->rules.num_philos);
	d->sem.global.print = create_sem(SEM_PRINT_NAME, 1);
	d->sem.global.start = create_sem(SEM_START_NAME, 0);
	d->sem.global.ready = create_sem(SEM_READY_NAME, 0);
	d->sem.global.stop = create_sem(SEM_STOP_NAME, 0);
	d->sem.global.stop_received = create_sem(SEM_STOP_RECEIVED_NAME, 0);
	d->sem.global.stuffed = create_sem(SEM_STUFFED_NAME, 0);
	if (d->sem.global.forks == SEM_FAILED
		|| d->sem.global.print == SEM_FAILED
		|| d->sem.global.start == SEM_FAILED
		|| d->sem.global.ready == SEM_FAILED
		|| d->sem.global.stop == SEM_FAILED
		|| d->sem.global.stop_received == SEM_FAILED
		|| d->sem.global.stuffed == SEM_FAILED)
		error_out(d, ESEM);
}
