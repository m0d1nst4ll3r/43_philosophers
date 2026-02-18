/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:38:11 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/18 19:04:19 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_prog(t_prog *d)
{
	int	i;

	d->is_parent = true;
	d->sem.forks.ref = SEM_FAILED;
	d->sem.print.ref = SEM_FAILED;
	d->sem.start.ref = SEM_FAILED;
	d->sem.death.ref = SEM_FAILED;
	d->sem.stop.ref = SEM_FAILED;
	d->sem.error.ref = SEM_FAILED;
	i = 0;
	while (i < d->rules.num_philos)
	{
		d->sem.stuffed[i].ref = SEM_FAILED;
		i++;
	}
}
