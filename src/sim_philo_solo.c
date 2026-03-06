/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_philo_solo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:23:20 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/06 15:28:28 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	solo_philo(t_prog *d)
{
	sem_wait(d->sem.global.print);
	if (!d->stop)
	{
		gettimeofday(&d->time.current, NULL);
		printf("%d %d is thinking\n", ft_time_sub(d->time.current,
				d->time.start) / 1000, d->philo_id + 1);
		printf("%d %d has taken a fork\n", ft_time_sub(d->time.current,
				d->time.start) / 1000, d->philo_id + 1);
	}
	sem_post(d->sem.global.print);
}
