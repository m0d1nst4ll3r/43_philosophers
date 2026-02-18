/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:42:23 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/18 17:53:38 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_args(t_prog *d)
{
	if (ft_atox(av[1], 0, &d->rules.num_philos,
			sizeof(d->rules.num_philos) | ATOX_U) < 0
		|| !d->rules.num_philos
		|| ft_atox(av[2], 0, &d->rules.time_to_die,
			sizeof(d->rules.time_to_die) | ATOX_U) < 0
		|| ft_atox(av[3], 0, &d->rules.time_to_eat,
			sizeof(d->rules.time_to_eat) | ATOX_U) < 0
		|| ft_atox(av[4], 0, &d->rules.time_to_sleep,
			sizeof(d->rules.time_to_sleep) | ATOX_U) < 0
		|| (av[5] && ft_atox(av[5], 0, &d->rules.meals_to_end,
				sizeof(d->rules.meals_to_end) | ATOX_U) < 0))
		return (false);
	return (true);
}
