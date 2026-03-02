/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:53:31 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/02 18:20:21 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_error(char *err_str)
{
	unsigned int	i;

	if (!err_str)
		err_str = EDEFAULT;
	i = 0;
	while (err_str[i])
		i++;
	write(2, "philo: ", 7);
	write(2, err_str, i);
	write(2, "\n", 1);
}

void	error_out(t_prog *d, char *err_str)
{
	print_error(err_str);
	cleanup_prog(d);
	exit(1);
}
