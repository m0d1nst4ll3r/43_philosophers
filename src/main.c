/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:41:01 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/19 18:36:51 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_usage(void)
{
	printf("./philo number_of_philosophers time_to_die time_to_eat time_to_sleep\
 [number_of_times_each_philosopher_must_eat]\n\
Params should be unsigned integers. Need at least 1 philosopher.\n");
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
	prepare_sim(&data);
	supervise_sim(&data);
	end_sim(&data);
	exit_prog(&data, 0);
}
