/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:42:37 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/18 20:02:42 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_malloc(t_prog *d)
{
	d->philo_pids = malloc(sizeof(*d->philo_pids) * d->rules.num_philos);
	d->sem.stuffed = malloc(sizeof(*d->sem.stuffed) * d->rules.num_philos);
	if (!d->children_pids || !d->sem.stuffed)
		error_out(d, EMALLOC);
	memset(d->philo_pids, 0, sizeof(*d->philo_pids) * d->rules.num_philos);
	memset(d->sem.stuffed, 0, sizeof(*d->sem.stuffed) * d->rules.num_philos);
}
