/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:39:58 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/05 16:01:00 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	signal_stop(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->rules.num_philos + 1)
	{
		sem_post(d->sem.global.stop);
		i++;
	}
}

void	signal_start(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->rules.num_philos)
	{
		sem_post(d->sem.global.start);
		i++;
	}
}

void	wait_stop_received(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->rules.num_philos + 1)
	{
		sem_wait(d->sem.global.stop_received);
		i++;
	}
}
