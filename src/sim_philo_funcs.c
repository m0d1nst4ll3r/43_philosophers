/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_philo_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:41:14 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/02 13:59:24 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	p_think(t_prog *d)
{
//	printf("\t%d: think\n", d->philo_id + 1);
	sem_wait(d->sem.global.print);
	if (d->stop)
	{
		sem_post(d->sem.global.print);
		return (false);
	}
	gettimeofday(&d->time.current, NULL);
	printf("%d %d is thinking\n",
		ft_time_sub(d->time.current, d->time.start) / 1000, d->philo_id + 1);
	sem_post(d->sem.global.print);
	if (!d->time.meals_eaten && d->philo_id % 2)
		usleep(d->rules.time_to_eat * 1000);
	return (true);
}

bool	p_eat(t_prog *d)
{
//	printf("\t%d: eat\n", d->philo_id + 1);
	if (d->rules.num_philos == 1)
		return (false);
	sem_wait(d->sem.global.forks);
//	printf("\t\t%d: took fork\n", d->philo_id + 1);
	sem_wait(d->sem.global.forks);
//	printf("\t\t%d: took fork\n", d->philo_id + 1);
	sem_wait(d->sem.global.print);
	if (d->stop)
	{
		sem_post(d->sem.global.forks);
		sem_post(d->sem.global.forks);
		sem_post(d->sem.global.print);
		return (false);
	}
	gettimeofday(&d->time.current, NULL);
	sem_wait(d->sem.philo.death_value);
	d->time.death = ft_time_add(d->time.current, d->rules.time_to_die * 1000);
	sem_post(d->sem.philo.death_value);
	printf("%d %d is eating\n",
		ft_time_sub(d->time.current, d->time.start) / 1000, d->philo_id + 1);
	sem_post(d->sem.global.print);
	usleep(d->rules.time_to_eat * 1000);
	sem_post(d->sem.global.forks);
//	printf("\t\t%d: replaced fork\n", d->philo_id + 1);
	sem_post(d->sem.global.forks);
//	printf("\t\t%d: replaced fork\n", d->philo_id + 1);
	if (++d->time.meals_eaten == d->rules.meals_to_end)
		sem_post(d->sem.global.stuffed);
	return (true);
}

bool	p_sleep(t_prog *d)
{
//	printf("\t%d: sleep\n", d->philo_id + 1);
	sem_wait(d->sem.global.print);
	if (d->stop)
	{
		sem_post(d->sem.global.print);
		return (false);
	}
	gettimeofday(&d->time.current, NULL);
	printf("%d %d is sleeping\n",
		ft_time_sub(d->time.current, d->time.start) / 1000, d->philo_id + 1);
	sem_post(d->sem.global.print);
	usleep(d->rules.time_to_sleep * 1000);
	return (true);
}
