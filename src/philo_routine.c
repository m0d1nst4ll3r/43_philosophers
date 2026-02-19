/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:43:03 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/19 19:17:21 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_start(t_prog *d)
{
	while (!sem_exists(d->sem.start.name)
		&& !sem_exists(d->sem.stop.name))
		;
}

static void	update_start_time(t_prog *d)
{
	gettimeofday(&d->time.start, NULL);
	d->time.death = ft_time_add(d->time.start, d->rules.time_to_die);
}

static void	philo_loop(t_prog *d)
{
	while (p_think(d) && p_eat(d) && p_sleep(d))
		;
}

void	philo_routine(t_prog *d)
{
	wait_start(d);
	update_start_time(d);
	philo_loop(d);
}
