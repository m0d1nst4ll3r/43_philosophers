#include "philo.h"

// Posting + 1 times for main thread
// Used in stuffed watcher thread and death watcher thread
static void	post_stop_loop(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->rules.num_philos + 1)
	{
		sem_post(d->sem.global.stop);
		i++;
	}
}

// Waiting + 1 times for main thread
// Used in stuffed watcher thread and death watcher thread
static void	wait_stop_received(t_prog *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->rules.num_philos + 1)
	{
		sem_wait(d->sem.global.stop_received);
		i++;
	}
}

// Created from main - will set stop if all philos are stuffed
void	*stuffed_watcher_thread(void *p)
{
	t_prog	*d
	int		i;

	d = p;
	i = 0;
	while (i < d->rules.num_philos)
	{
		if (d->stop)
			break ;
		sem_wait(d->sem.global.stuffed);
		i++;
	}
	sem_wait(d->sem.global.print);
	if (d->stop)
	{
		sem_post(d->sem.global.print);
		return (NULL);
	}
	post_stop_loop(d->sem.global.stop);
	wait_stop_received(d->sem.global.stop);
	sem_post(d->sem.global.print);
	return (NULL);
}

static void	signal_death(t_prog *d)
{
	sem_wait(d->sem.global.print);
	if (d->stop)
	{
		sem_post(d->sem.global.print);
		return ;
	}
	gettimeofday(&d->time.current);
	printf("%d %d died\n",	ft_time_sub(d->time.current, d->time.start) / 1000, d->philo_id);
	post_stop_loop(d);
	wait_stop_received(d);
	sem_post(d->sem.global.print);
}

// Created from philos - will set stop and print death msg if philo dies
void	*death_watcher_thread(void *p)
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
		if (ft_time_sub(current_time, death_time) >= 0)
			break ;
		usleep(SUPERVISOR_USLEEP);
	}
	signal_death(d);
	return (NULL);
}

// Created from philos - watches for stop value, tells philo to stop
void	*stop_watcher_thread(t_prog *d)
{
	sem_wait(d->sem.global.stop);
	d->stop = true;
	sem_post(d->sem.global.stop_received);
}

static void	wait_stop(t_prog *d)
{
	sem_wait(d->sem.global.stop);
	d->stop = true;
	sem_post(d->sem.global.stop_received);
}

void	main_routine(t_prog *d)
{
	create_stuffed_watcher(d);
	wait_stop(d);
	stop_stuffed_watcher(d);
} // Cleanup after this (shared with philos)






