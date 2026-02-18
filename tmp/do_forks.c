/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_forks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:35:27 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/18 19:18:27 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_forks(t_prog *d)
{
	while (d->philo_id < d->rules.num_philos)
	{
		d->philo_pids[i] = fork();
		if (d->philo_pids[i] == -1)
			error_stop(d, EFORK);
		else if (!d->philo_pids[i])
		{
			d->is_parent = false;
			break ;
		}
		d->philo_id++;
	}
	if (!is_parent)
		philo_routine(d);
	else
		supervisor_routine(d);
}
