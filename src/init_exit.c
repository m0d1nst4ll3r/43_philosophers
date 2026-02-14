/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:06:55 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/14 16:08:53 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_prog(t_prog *d)
{
	d->philo = NULL;
}

void	exit_prog(t_prog *d, int exitval)
{
	ft_free((void *)&d->philo);
	exit(exitval);
}

void	print_usage(void)
{
	printf("philo:\n\t./philo   number_of_philosophers  time_to_die   \
time_to_eat   time_to_sleep   [number_of_times_to_eat]\n");
	exit(0);
}

void	error_out(t_prog *d, char *err_str)
{
	if (!err_str)
		err_str = DEFAULT_ERR;
	dprintf(2, "philo: %s", err_str);
	if (errno)
		dprintf(2, ": %s", strerror(errno));
	dprintf(2, "\n");
	exit_prog(d, 1);
}
