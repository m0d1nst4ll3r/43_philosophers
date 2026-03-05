/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_do_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:35:27 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/05 11:43:57 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// So that philos all have the same start time, we set it before forks
// Since preparations after forks (e.g creating threads) take time,
//	the sim will wait a certain time before really starting
void	do_forks(t_prog *d)
{
	gettimeofday(&d->time.start, NULL);
	d->time.start = ft_time_add(d->time.start, START_DELAY_USEC);
	d->time.death = ft_time_add(d->time.start, d->rules.time_to_die);
	while (d->philo_id < d->rules.num_philos)
	{
		d->philo_pids[d->philo_id] = fork();
		if (d->philo_pids[d->philo_id] == -1)
			error_stop_parent(d, EFORK);
		else if (!d->philo_pids[d->philo_id])
		{
			d->is_parent = false;
			break ;
		}
		d->philo_id++;
	}
	if (!d->is_parent)
		philo_routine(d);
	else
		main_routine(d);
}
