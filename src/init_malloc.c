/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:42:37 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/02 10:50:11 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_malloc(t_prog *d)
{
	int	size;

	size = sizeof(*d->philo_pids) * d->rules.num_philos;
	d->philo_pids = malloc(size);
	if (!d->philo_pids)
		error_out(d, EMALLOC);
	memset(d->philo_pids, 0, size);
}
