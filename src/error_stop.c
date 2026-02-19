/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:17:45 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/19 20:29:08 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	kill_philos(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->rules.num_philos)
	{
		kill(d->philo_pids[i], SIGKILL);
		i++;
	}
}

// Fires if stop sem can't be created - have to force kill children for lack
//	of any other way to tell them to stop
static void	critical_stop(t_prog *d)
{
	kill_philos(d);
	error_out(d, ESTOP);
}

void	error_stop(t_prog *d, char *err_str)
{
	d->sem.stop.ref = create_sem(d->sem.stop.name, 0);
	if (d->sem.stop.ref == SEM_FAILED)
		critical_stop(d);
	error_out(d, err_str);
}
