/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:53:31 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/19 20:31:07 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	exit_prog(t_prog *d, unsigned char exitval)
{
	cleanup_prog(d);
	exit(exitval);
}

void	error_out(t_prog *d, char *err_str)
{
	if (!err_str)
		err_str = EDEFAULT;
	dprintf(2, "philo: %s", err_str);
	if (errno)
		dprintf(2, ": %s", strerror(errno));
	dprintf(2, "\n");
	exit_prog(d, 1);
}
