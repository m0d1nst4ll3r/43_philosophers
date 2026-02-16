/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 02:49:31 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/16 02:50:31 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_sim(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->num_philos)
	{
		pthread_join(d->philos[i].thread, NULL);
		i++;
	}
}
