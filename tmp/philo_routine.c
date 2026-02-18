/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:43:03 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/18 20:16:15 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_start(t_prog *d)
{
	while (1)
	{
		if (sem_exists(d->sem.start.name)
			|| sem_exists(d->sem.stop.name))
			break ;
	}
}

static void	update_start_time(t_prog *d)
{
	//...
}

static void	philo_loop(t_prog *d)
{
	//...
}

void	philo_routine(t_prog *d)
{
	wait_start(d);
	update_start_time(d);
	philo_loop(d);
}

