/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 03:18:50 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/03 12:31:11 by rapohlen         ###   ########.fr       */
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

static void	increment_stuffed(t_philo *d)
{
	pthread_mutex_lock(d->mutex.stuffed_philos);
	(*d->time.stuffed_philos)++;
	pthread_mutex_unlock(d->mutex.stuffed_philos);
}

static bool	p_eat(t_philo *d)
{
	if (&d->mutex.lfork.obj == d->mutex.rfork)
		return (false);
	pthread_mutex_lock(&d->mutex.lfork.obj);
	pthread_mutex_lock(d->mutex.rfork);
	pthread_mutex_lock(d->mutex.print);
	if (*d->time.is_end_of_sim)
	{
		pthread_mutex_unlock(d->mutex.print);
		pthread_mutex_unlock(&d->mutex.lfork.obj);
		pthread_mutex_unlock(d->mutex.rfork);
		return (false);
	}
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
	if (++d->time.meals_eaten == d->rules.meals_to_end)
		increment_stuffed(d);
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

void	*philo_thread(void *p)
{
	t_philo	*d;

	d = p;
	pthread_mutex_lock(d->mutex.print);
	pthread_mutex_unlock(d->mutex.print);
	while (p_think(d) && p_eat(d) && p_sleep(d))
		;
	return (NULL);
}
