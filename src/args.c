/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:23:51 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/14 19:53:53 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_args(t_prog *d, char **av)
{
	d->time.is_eat_limit_set = false;
	if (av[5])
		d->time.is_eat_limit_set = true;
	if (ft_atox(av[1], 0, &d->num_philo, sizeof(d->num_philo) | ATOX_U) < 0
		|| ft_atox(av[2], 0, &d->time.die, sizeof(d->time.die) | ATOX_U) < 0
		|| ft_atox(av[3], 0, &d->time.eat, sizeof(d->time.eat) | ATOX_U) < 0
		|| ft_atox(av[4], 0, &d->time.sleep, sizeof(d->time.sleep) | ATOX_U) < 0
		|| (av[5] && ft_atox(av[5], 0, &d->time.eat_limit,
				sizeof(d->time.eat_limit) | ATOX_U) < 0))
		error_out(d, ERR_ARG);
}
