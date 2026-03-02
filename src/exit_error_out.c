/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:53:31 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/02 11:56:30 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	exit_prog(t_prog *d, unsigned char exitval)
{
	cleanup_prog(d);
	exit(exitval);
}

static void	print_error(char *err_str)
{
	unsigned int	i;

	if (!err_str)
		err_str = EDEFAULT;
	i = 0;
	while (err_str[i])
		i++;
	write(2, "philo : ", 8);
	write(2, err_str, i);
	write(2, "\n", 1);
}

void	error_out(t_prog *d, char *err_str)
{
	print_error(err_str);
	exit_prog(d, 1);
}
