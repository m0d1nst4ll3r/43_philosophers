/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:38:55 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/20 14:54:12 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_usage(void)
{
	printf("./philo number_of_philosophers time_to_die time_to_eat time_to_sleep\
 [number_of_times_each_philosopher_must_eat]\n\
Params should be unsigned integers <= 10000. Need at least 1 philosopher.\n");
}

int	main(int ac, char **av)
{
	t_prog	data;

	memset(&data, 0, sizeof(data));
	if ((ac != 5 && ac != 6) || !init_args(&data, av))
	{
		print_usage();
		return (0);
	}
	init_prog(&data);
	init_malloc(&data);
	init_sem_names(&data);
	init_sem_refs(&data);
	check_sems_avail(&data);
	do_forks(&data);
	cleanup_prog(&data);
	return (0);
}
