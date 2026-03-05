/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:48:17 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/05 12:08:14 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	increment_stuffed(t_philo *d)
{
	pthread_mutex_lock(d->mutex.stuffed_philos);
	(*d->time.stuffed_philos)++;
	pthread_mutex_unlock(d->mutex.stuffed_philos);
}

static bool	print_fork(t_philo *d, int fork_state)
{
	pthread_mutex_lock(d->mutex.print);
	if (*d->time.is_end_of_sim)
	{
		pthread_mutex_unlock(d->mutex.print);
		if (fork_state != 3)
			pthread_mutex_unlock(&d->mutex.lfork.obj);
		if (fork_state != 1)
			pthread_mutex_unlock(d->mutex.rfork);
		return (false);
	}
	gettimeofday(&d->time.current, NULL);
	printf("%d %d has taken a fork\n",
		ft_time_sub(d->time.current, d->time.start) / 1000, d->id + 1);
	pthread_mutex_unlock(d->mutex.print);
	return (true);
}

static bool	take_forks(t_philo *d)
{
	if (&d->mutex.lfork.obj < d->mutex.rfork)
	{
		pthread_mutex_lock(&d->mutex.lfork.obj);
		if (!print_fork(d, 1))
			return (false);
		pthread_mutex_lock(d->mutex.rfork);
		if (!print_fork(d, 2))
			return (false);
	}
	else
	{
		pthread_mutex_lock(d->mutex.rfork);
		if (!print_fork(d, 3))
			return (false);
		pthread_mutex_lock(&d->mutex.lfork.obj);
		if (!print_fork(d, 4))
			return (false);
	}
	return (true);
}

bool	p_eat(t_philo *d)
{
	if (&d->mutex.lfork.obj == d->mutex.rfork)
		return (false);
	if (!take_forks(d))
		return (false);
	pthread_mutex_lock(d->mutex.print);
	if (*d->time.is_end_of_sim)
	{
		pthread_mutex_unlock(d->mutex.print);
		pthread_mutex_unlock(&d->mutex.lfork.obj);
		pthread_mutex_unlock(d->mutex.rfork);
		return (false);
	}
	if (++d->time.meals_eaten == d->rules.meals_to_end)
		increment_stuffed(d);
	gettimeofday(&d->time.current, NULL);
	pthread_mutex_lock(&d->mutex.death_time.obj);
	d->time.death = ft_time_add(d->time.current, d->rules.time_to_die);
	pthread_mutex_unlock(&d->mutex.death_time.obj);
	printf("%d %d is eating\n",
		ft_time_sub(d->time.current, d->time.start) / 1000, d->id + 1);
	pthread_mutex_unlock(d->mutex.print);
	usleep(d->rules.time_to_eat);
	pthread_mutex_unlock(&d->mutex.lfork.obj);
	pthread_mutex_unlock(d->mutex.rfork);
	return (true);
}
