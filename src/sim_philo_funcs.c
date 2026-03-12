/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_philo_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:41:14 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/11 19:49:42 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	p_think(t_prog *d)
{
	sem_wait(d->sem.global.print);
	if (d->stop)
	{
		sem_post(d->sem.global.print);
		return (false);
	}
	gettimeofday(&d->time.current, NULL);
	printf("%d %d is thinking\n",
		ft_time_sub(d->time.current, d->time.start) / 1000, d->philo_id + 1);
	sem_post(d->sem.global.print);
	if (!d->time.meals_eaten && d->philo_id % 2)
		usleep(d->rules.time_to_eat / 2);
	else if (d->rules.num_philos % 2)
		usleep(PHILO_ODD_USLEEP);
	return (true);
}

bool	p_sleep(t_prog *d)
{
	sem_wait(d->sem.global.print);
	if (d->stop)
	{
		sem_post(d->sem.global.print);
		return (false);
	}
	gettimeofday(&d->time.current, NULL);
	printf("%d %d is sleeping\n",
		ft_time_sub(d->time.current, d->time.start) / 1000, d->philo_id + 1);
	sem_post(d->sem.global.print);
	usleep(d->rules.time_to_sleep);
	return (true);
}
