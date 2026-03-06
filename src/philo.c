/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 03:18:50 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/06 15:31:24 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	p_think(t_philo *d)
{
	pthread_mutex_lock(d->mutex.print);
	if (*d->time.is_end_of_sim)
	{
		pthread_mutex_unlock(d->mutex.print);
		return (false);
	}
	gettimeofday(&d->time.current, NULL);
	printf("%d %d is thinking\n",
		ft_time_sub(d->time.current, d->time.start) / 1000, d->id + 1);
	pthread_mutex_unlock(d->mutex.print);
	if (!d->time.meals_eaten && d->id % 2)
		usleep(d->rules.time_to_eat / 2);
	return (true);
}

static bool	p_sleep(t_philo *d)
{
	pthread_mutex_lock(d->mutex.print);
	if (*d->time.is_end_of_sim)
	{
		pthread_mutex_unlock(d->mutex.print);
		return (false);
	}
	gettimeofday(&d->time.current, NULL);
	printf("%d %d is sleeping\n",
		ft_time_sub(d->time.current, d->time.start) / 1000, d->id + 1);
	pthread_mutex_unlock(d->mutex.print);
	usleep(d->rules.time_to_sleep);
	return (true);
}

static void	solo_philo(t_philo *d)
{
	pthread_mutex_lock(d->mutex.print);
	if (!*d->time.is_end_of_sim)
	{
		gettimeofday(&d->time.current, NULL);
		printf("%d %d is thinking\n",
			ft_time_sub(d->time.current, d->time.start) / 1000, d->id + 1);
		printf("%d %d has taken a fork\n",
			ft_time_sub(d->time.current, d->time.start) / 1000, d->id + 1);
	}
	pthread_mutex_unlock(d->mutex.print);
}

void	*philo_thread(void *p)
{
	t_philo	*d;

	d = p;
	pthread_mutex_lock(d->mutex.print);
	pthread_mutex_unlock(d->mutex.print);
	if (&d->mutex.lfork.obj == d->mutex.rfork)
	{
		solo_philo(d);
		return (NULL);
	}
	while (p_think(d) && p_eat(d) && p_sleep(d))
		;
	return (NULL);
}
