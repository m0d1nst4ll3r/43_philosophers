/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_philo_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:43:03 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/02 17:13:34 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_death_value_sem(t_prog *d)
{
	char	*sem_name;
	char	*id_str;

	id_str = ft_itoa(d->philo_id);
	if (!id_str)
		error_stop_philo(d, EMALLOC);
	sem_name = ft_strjoin(SEM_DEATH_VALUE_NAME, id_str);
	free(id_str);
	if (!sem_name)
		error_stop_philo(d, EMALLOC);
	d->sem.philo.death_value = create_sem(sem_name, 1);
	if (d->sem.philo.death_value == SEM_FAILED)
	{
		free(sem_name);
		error_stop_philo(d, ESEM);
	}
	sem_unlink(sem_name);
	free(sem_name);
}

static void	signal_death(t_prog *d)
{
	sem_wait(d->sem.global.print);
	if (d->stop)
	{
		sem_post(d->sem.global.print);
		return ;
	}
	gettimeofday(&d->time.current, NULL);
	printf("%d %d died\n",
		ft_time_sub(d->time.current, d->time.start) / 1000, d->philo_id + 1);
	signal_stop(d);
	wait_stop_received(d);
	sem_post(d->sem.global.print);
}

static void	*death_watcher_thread(void *p)
{
	struct timeval	death_time;
	struct timeval	current_time;
	t_prog			*d;

	d = p;
	while (1)
	{
		sem_wait(d->sem.philo.death_value);
		death_time = d->time.death;
		sem_post(d->sem.philo.death_value);
		gettimeofday(&current_time, NULL);
		if ((current_time.tv_sec == death_time.tv_sec
				&& current_time.tv_usec >= death_time.tv_usec)
			|| current_time.tv_sec > death_time.tv_sec)
			break ;
		usleep(SUPERVISOR_USLEEP);
	}
	signal_death(d);
	return (NULL);
}

// Created from philos - watches for stop value, tells philo to stop
static void	*stop_watcher_thread(void *p)
{
	t_prog	*d;

	d = p;
	sem_wait(d->sem.global.stop);
	d->stop = true;
	sem_post(d->sem.global.stop_received);
	return (NULL);
}

// Norm prevents me from doing small static functions (> 5)
// 1. Create death value sem (with philo_id, has to be unique)
// 2. Create death watcher thread and stop watcher thread
// 3. Signal ready and wait start
// 4. Update start time (and death time)
// 5. Run the philo logic loop
// 6. Reset death time for death watcher to exit
void	philo_routine(t_prog *d)
{
	create_death_value_sem(d);
	if (pthread_create(&d->threads.philo_stop_watcher.thread, NULL,
			stop_watcher_thread, d))
		error_stop_philo(d, ETHREAD);
	d->threads.philo_stop_watcher.is_created = true;
	if (pthread_create(&d->threads.philo_death_watcher.thread, NULL,
			death_watcher_thread, d))
		error_stop_philo(d, ETHREAD);
	d->threads.philo_death_watcher.is_created = true;
	sem_post(d->sem.global.ready);
	sem_wait(d->sem.global.start);
	gettimeofday(&d->time.start, NULL);
	d->time.death = ft_time_add(d->time.start, d->rules.time_to_die);
	while (p_think(d) && p_eat(d) && p_sleep(d))
		;
	if (d->stop)
	{
		sem_wait(d->sem.philo.death_value);
		d->time.death = d->time.start;
		sem_post(d->sem.philo.death_value);
	}
}
