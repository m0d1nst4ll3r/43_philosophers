/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 19:17:45 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/18 19:18:27 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_stop(t_prog *d, char *err_str)
{
	d->sem.stop.ref = create_sem(d->sem.stop.name, 0);
	if (d->sem.stop.ref == SEM_FAILED)
		error_out(d, ESTOP);
	error_out(d, err_str);
}
