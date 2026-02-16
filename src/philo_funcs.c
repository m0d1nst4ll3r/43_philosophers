/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 02:43:04 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/16 10:27:47 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_end_of_sim(t_philo *d)
{
	bool	is_end_of_sim;

	pthread_mutex_lock(d->mutex.is_end_of_sim);
	is_end_of_sim = *d->time.is_end_of_sim;
	pthread_mutex_unlock(d->mutex.is_end_of_sim);
	return (is_end_of_sim);
}

bool	p_think(t_philo *d)
{
	pthread_mutex_lock(d->mutex.print);
	if (is_end_of_sim(d))
	{
		pthread_mutex_unlock(d->mutex.print);
		return (false);
	}
	gettimeofday(&d->time.current, NULL);
	printf("%d %d is thinking\n",
		ft_time_sub(d->time.current, d->time.start) / 1000, d->id + 1);
	pthread_mutex_unlock(d->mutex.print);
	if (!d->time.meals_eaten && d->id % 2)
		usleep(d->time.to_eat * 1000);
	return (true);
}

static void	increment_stuffed(t_philo *d)
{
	pthread_mutex_lock(d->mutex.stuffed_philos);
	(*d->time.stuffed_philos)++;
	pthread_mutex_unlock(d->mutex.stuffed_philos);
}

bool	p_eat(t_philo *d)
{
	pthread_mutex_lock(&d->mutex.lfork);
	pthread_mutex_lock(d->mutex.rfork);
	pthread_mutex_lock(d->mutex.print);
	if (is_end_of_sim(d))
	{
		pthread_mutex_unlock(d->mutex.print);
		pthread_mutex_unlock(&d->mutex.lfork);
		pthread_mutex_unlock(d->mutex.rfork);
		return (false);
	}
	gettimeofday(&d->time.current, NULL);
	pthread_mutex_lock(&d->mutex.death_time);
	d->time.death = ft_time_add(d->time.current, d->time.to_die * 1000);
	pthread_mutex_unlock(&d->mutex.death_time);
	printf("%d %d is eating\n",
		ft_time_sub(d->time.current, d->time.start) / 1000, d->id + 1);
	pthread_mutex_unlock(d->mutex.print);
	usleep(d->time.to_eat * 1000);
	pthread_mutex_unlock(&d->mutex.lfork);
	pthread_mutex_unlock(d->mutex.rfork);
	if (++d->time.meals_eaten == d->time.meals_to_end)
		increment_stuffed(d);
	return (true);
}

bool	p_sleep(t_philo *d)
{
	pthread_mutex_lock(d->mutex.print);
	if (is_end_of_sim(d))
	{
		pthread_mutex_unlock(d->mutex.print);
		return (false);
	}
	gettimeofday(&d->time.current, NULL);
	printf("%d %d is sleeping\n",
		ft_time_sub(d->time.current, d->time.start) / 1000, d->id + 1);
	pthread_mutex_unlock(d->mutex.print);
	usleep(d->time.to_sleep * 1000);
	return (true);
}
