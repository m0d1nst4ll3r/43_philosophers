/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:41:14 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/19 20:39:05 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	p_die(t_prog *d)
{
	int	usec_until_death;

	gettimeofday(&d->time.current, NULL);
	usec_until_death = ft_time_sub(d->time.death, d->time.current);
	if (usec_until_death > 0)
		usleep(usec_until_death);
	sem_wait(d->sem.print.ref);
	if (!sem_exists(d->sem.death.name))
	{
		d->sem.death.ref = create_sem(d->sem.death.name, 0);
		if (d->sem.death.ref == SEM_FAILED)
			error_stop(d, ESEM);
		gettimeofday(&d->time.current, NULL);
		printf("%d %d died\n",
			ft_time_sub(d->time.current, d->time.start), d->philo_id + 1);
		while (!sem_exists(d->sem.stop.name))
			;
	}
	sem_post(d->sem.print.ref);
	return (false);
}

static bool	p_usleep(t_prog *d, unsigned int usec)
{
	gettimeofday(&d->time.current, NULL);
	if (ft_time_sub(d->time.death, ft_time_add(d->time.current, usec)) <= 0)
		return (false);
	usleep(usec);
	return (true);
}

bool	p_think(t_prog *d)
{
	sem_wait(d->sem.print.ref);
	if (sem_exists(d->sem.stop.name))
	{
		sem_post(d->sem.print.ref);
		return (false);
	}
	gettimeofday(&d->time.current, NULL);
	printf("%d %d is thinking\n",
		ft_time_sub(d->time.current, d->time.start) / 1000, d->philo_id + 1);
	sem_post(d->sem.print.ref);
	if (!d->time.meals_eaten && d->philo_id % 2)
	{
		if (!p_usleep(d, d->rules.time_to_eat * 1000))
			return (p_die(d));
	}
	return (true);
}

bool	p_eat(t_prog *d)
{
	if (d->rules.num_philos == 1)
		return (p_die(d));
	sem_wait(d->sem.forks.ref);
	sem_wait(d->sem.forks.ref);
	sem_wait(d->sem.print.ref);
	if (sem_exists(d->sem.stop.name))
	{
		sem_post(d->sem.forks.ref);
		sem_post(d->sem.forks.ref);
		sem_post(d->sem.print.ref);
		return (false);
	}
	gettimeofday(&d->time.current, NULL);
	d->time.death = ft_time_add(d->time.current, d->rules.time_to_die);
	printf("%d %d is eating\n",
		ft_time_sub(d->time.current, d->time.start) / 1000, d->philo_id + 1);
	if (!p_usleep(d, d->rules.time_to_eat * 1000))
		return (p_die(d));
	sem_post(d->sem.print.ref);
	sem_post(d->sem.forks.ref);
	sem_post(d->sem.forks.ref);
	if (++d->time.meals_eaten == d->rules.meals_to_end)
	{
		d->sem.stuffed[d->philo_id].ref = create_sem(d->sem.stuffed[d->philo_id].name, 0);
		if (d->sem.stuffed[d->philo_id].ref == SEM_FAILED)
			error_stop(d, ESEM);
	}
	return (true);
}

bool	p_sleep(t_prog *d)
{
	sem_wait(d->sem.print.ref);
	if (sem_exists(d->sem.stop.name))
	{
		sem_post(d->sem.print.ref);
		return (false);
	}
	gettimeofday(&d->time.current, NULL);
	printf("%d %d is sleeping\n",
		ft_time_sub(d->time.current, d->time.start) / 1000, d->philo_id + 1);
	if (!p_usleep(d, d->rules.time_to_sleep * 1000))
		return (p_die(d));
	sem_post(d->sem.print.ref);
	return (true);
}
