/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:23:51 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/19 18:35:04 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_args(t_prog *d, char **av)
{
	if (ft_atox(av[1], 0, &d->num_philos, sizeof(d->num_philos) | ATOX_U) < 0
		|| !d->num_philos
		|| ft_atox(av[2], 0, &d->time.to_die,
			sizeof(d->time.to_die) | ATOX_U) < 0
		|| ft_atox(av[3], 0, &d->time.to_eat,
			sizeof(d->time.to_eat) | ATOX_U) < 0
		|| ft_atox(av[4], 0, &d->time.to_sleep,
			sizeof(d->time.to_sleep) | ATOX_U) < 0
		|| (av[5] && ft_atox(av[5], 0, &d->time.meals_to_end,
				sizeof(d->time.meals_to_end) | ATOX_U) < 0))
		return (false);
	return (true);
}
