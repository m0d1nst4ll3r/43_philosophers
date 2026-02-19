/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sems_avail.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:07:58 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/19 20:37:28 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_sem_available(char *sem_name)
{
	sem_t	*new_sem;

	sem_unlink(sem_name);
	new_sem = sem_open(sem_name, O_CREAT | O_EXCL, 0600, 0);
	if (new_sem == SEM_FAILED)
		return (false);
	sem_close(new_sem);
	sem_unlink(sem_name);
	return (true);
}

static bool	are_stuffed_sems_available(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->rules.num_philos)
	{
		if (!is_sem_available(d->sem.stuffed[i].name))
			return (false);
		i++;
	}
	return (true);
}

void	check_sems_avail(t_prog *d)
{
	if (!is_sem_available(d->sem.start.name)
		|| !is_sem_available(d->sem.death.name)
		|| !is_sem_available(d->sem.stop.name)
		|| !are_stuffed_sems_available(d))
		error_out(d, ESEMAVAIL);
}
