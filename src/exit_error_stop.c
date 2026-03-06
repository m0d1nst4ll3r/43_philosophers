/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error_stop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:17:45 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/06 14:54:11 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Fires in case of fork failure or parent thread create failure
void	error_stop_parent(t_prog *d, char *err_str)
{
	sem_wait(d->sem.global.print);
	if (!d->stop)
		signal_stop(d);
	sem_post(d->sem.global.print);
	signal_start(d);
	error_out(d, err_str);
}

// Fires in case of child malloc/sem/thread create failure
void	error_stop_philo(t_prog *d, char *err_str)
{
	sem_wait(d->sem.global.print);
	if (!d->stop)
	{
		signal_stop(d);
		wait_stop_received(d);
	}
	sem_post(d->sem.global.print);
	sem_post(d->sem.global.ready);
	error_out(d, err_str);
}
