/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sem_refs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:45:45 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/18 18:02:02 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_sem_refs(t_prog *d)
{
	d->sem.forks.ref = create_sem(d->sem.forks.name, d->rules.num_philos);
	d->sem.print.ref = create_sem(d->sem.print.name, 1);
	if (d->sem.forks.ref == SEM_FAILED || d->sem.print.ref == SEM_FAILED)
		error_out(d, ESEM);
}

