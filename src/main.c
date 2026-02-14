/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:41:01 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/14 16:09:21 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_prog	data;

	if (ac != 5 && ac != 6)
		print_usage();
	init_prog(&data);
	parse_args(&data, av);
	exit_prog(&data, 0);
}
