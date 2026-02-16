/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise_sim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 01:59:16 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/16 06:19:35 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_end_of_sim(t_prog *d)
{
	pthread_mutex_lock(&d->mutex.is_end_of_sim);
	d->time.is_end_of_sim = true;
	pthread_mutex_unlock(&d->mutex.is_end_of_sim);
}

static bool	check_deaths(t_prog *d)
{
	unsigned int	i;
	struct timeval	death_time;

	i = 0;
	while (i < d->num_philos)
	{
		pthread_mutex_lock(&d->philos[i].mutex.death_time);
		death_time = d->philos[i].time.death;
		pthread_mutex_unlock(&d->philos[i].mutex.death_time);
		if (ft_time_sub(death_time, d->time.current) <= 0)
		{
			set_end_of_sim(d);
			pthread_mutex_lock(&d->mutex.print);
			printf("%d %d died\n", ft_time_sub(death_time,
					d->time.start) / 1000, i + 1);
			pthread_mutex_unlock(&d->mutex.print);
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	check_stuffed(t_prog *d)
{
	unsigned int	stuffed_philos;

	pthread_mutex_lock(&d->mutex.stuffed_philos);
	stuffed_philos = d->time.stuffed_philos;
	pthread_mutex_unlock(&d->mutex.stuffed_philos);
	if (stuffed_philos == d->num_philos)
	{
		set_end_of_sim(d);
		return (true);
	}
	return (false);
}

void	supervise_sim(t_prog *d)
{
	while (1)
	{
		gettimeofday(&d->time.current, NULL);
		if (check_deaths(d) || check_stuffed(d))
			return ;
		usleep(SUPERVISOR_USLEEP);
	}
}
