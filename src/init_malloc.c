/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:42:37 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/19 20:32:19 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_stuffed(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->rules.num_philos)
	{
		d->sem.stuffed[i].ref = SEM_FAILED;
		i++;
	}
}

void	init_malloc(t_prog *d)
{
	d->philo_pids = malloc(sizeof(*d->philo_pids) * d->rules.num_philos);
	if (!d->philo_pids)
		error_out(d, EMALLOC);
	memset(d->philo_pids, 0, sizeof(*d->philo_pids) * d->rules.num_philos);
	d->sem.stuffed = malloc(sizeof(*d->sem.stuffed) * d->rules.num_philos);
	if (!d->sem.stuffed)
		error_out(d, EMALLOC);
	memset(d->sem.stuffed, 0, sizeof(*d->sem.stuffed) * d->rules.num_philos);
	init_stuffed(d);
}
