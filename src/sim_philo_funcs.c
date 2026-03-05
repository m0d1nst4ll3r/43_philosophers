/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_philo_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:41:14 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/05 11:39:00 by rapohlen         ###   ########.fr       */
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

static bool	print_fork(t_prog *d, int forks_taken)
{
	sem_wait(d->sem.global.print);
	if (d->stop)
	{
		sem_post(d->sem.global.forks);
		if (forks_taken == 2)
			sem_post(d->sem.global.forks);
		sem_post(d->sem.global.print);
		return (false);
	}
	gettimeofday(&d->time.current, NULL);
	printf("%d %d has taken a fork\n",
		ft_time_sub(d->time.current, d->time.start) / 1000, d->philo_id + 1);
	sem_post(d->sem.global.print);
	return (true);
}

static bool	take_forks(t_prog *d)
{
	sem_wait(d->sem.global.forks);
	if (!print_fork(d, 1))
		return (false);
	sem_wait(d->sem.global.forks);
	if (!print_fork(d, 2))
		return (false);
	return (true);
}

bool	p_eat(t_prog *d)
{
	if (d->rules.num_philos == 1)
		return (false);
	if (!take_forks(d))
		return (false);
	sem_wait(d->sem.global.print);
	if (d->stop)
	{
		sem_post(d->sem.global.forks);
		sem_post(d->sem.global.forks);
		sem_post(d->sem.global.print);
		return (false);
	}
	if (++d->time.meals_eaten == d->rules.meals_to_end)
		sem_post(d->sem.global.stuffed);
	gettimeofday(&d->time.current, NULL);
	sem_wait(d->sem.philo.death_value);
	d->time.death = ft_time_add(d->time.current, d->rules.time_to_die);
	sem_post(d->sem.philo.death_value);
	printf("%d %d is eating\n",
		ft_time_sub(d->time.current, d->time.start) / 1000, d->philo_id + 1);
	sem_post(d->sem.global.print);
	usleep(d->rules.time_to_eat);
	sem_post(d->sem.global.forks);
	sem_post(d->sem.global.forks);
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
