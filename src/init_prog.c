/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:38:11 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/23 15:38:12 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_prog(t_prog *d)
{
	d->is_parent = true;
	d->sem.global.forks = SEM_FAILED;
	d->sem.global.print = SEM_FAILED;
	d->sem.global.start = SEM_FAILED;
	d->sem.global.ready = SEM_FAILED;
	d->sem.global.stop = SEM_FAILED;
	d->sem.global.stop_received = SEM_FAILED;
	d->sem.global.stuffed = SEM_FAILED;
	d->sem.philo.death_value = SEM_FAILED;
}
