/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise_sim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 01:59:16 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/19 16:45:37 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			pthread_mutex_lock(&d->mutex.print);
			d->time.is_end_of_sim = true;
			gettimeofday(&d->time.current, NULL);
			printf("%d %d died\n", ft_time_sub(d->time.current, d->time.start) / 1000, i + 1);
//			print_message(ft_time_sub(d->time.current,
//					d->time.start) / 1000, i + 1, "died\n");
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
		pthread_mutex_lock(&d->mutex.print);
		d->time.is_end_of_sim = true;
		pthread_mutex_unlock(&d->mutex.print);
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
