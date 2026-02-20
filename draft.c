void	*stuffed_supervisor(void *p)
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
	sem_post(d->sem.global.stop);
	return (NULL);
}

static void	post_stop(t_prog *d)
{
	sem_wait(d->sem.global.print);
	if (d->stop)
	{
		sem_post(d->sem.global.print);
		return ;
	}
	gettimeofday(&d->time.current);
	printf("%d %d died\n", ft_time_sub(d->time.current, d->time.start) / 1000, d->philo_id);
	sem_post(d->sem.global.print);
}

void	*death_supervisor(void *p)
{
	t_prog	*d;

	d = p;
	while ()
	{
		usleep(SUPERVISOR_USLEEP);
	}
	post_stop(d);
	return (NULL);
}
