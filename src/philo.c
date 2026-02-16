/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 03:18:50 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/16 07:06:50 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_thread(void *p)
{
	t_philo	*d;

	d = p;
	pthread_mutex_lock(d->mutex.print);
	pthread_mutex_unlock(d->mutex.print);
	while (1)
	{
		if (!p_think(d) || !p_eat(d) || !p_sleep(d))
			return (NULL);
	}
	return (NULL);
}
