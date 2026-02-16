/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:41:01 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/16 03:21:39 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	Program flow:
//
// 1. Get args
// 2. Prepare sim
//	- Prepare philo structs (set addresses, values, etc)
//	- Init mutexes
//	- Init threads
//	- Init time
// 3. Supervise threads (threads have started now)
//	- Check deaths
//	- Check stuffed
// 4. End sim (join threads)
int	main(int ac, char **av)
{
	t_prog	data;

	if (ac != 5 && ac != 6)
		print_usage();
	init_prog(&data);
	parse_args(&data, av);
	prepare_sim(&data);
	supervise_sim(&data);
	end_sim(&data);
	exit_prog(&data, 0);
}
