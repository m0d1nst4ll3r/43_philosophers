#include "philo.h"

// This only monitors the global death semaphore
// Don't need to post global_death_sem since this is the only place it waits
void	*death_monitor(void *p)
{
	t_supervisor_death_monitor	*d;

	d = p;
	sem_wait(d->global_death_sem);
	sem_wait(d->local_death_var_sem);
	*d->is_philo_dead = true;
	sem_post(d->local_death_var_sem);
	return (NULL);
}

// This only monitors the global stuffed semaphore
// Don't need to post global_stuffed_sem
void	*stuffed_monitor(void *p)
{
	int							i;
	t_supervisor_stuffed_monitor	*d;

	d = p;
	i = 0;
	while (i < d->num_philos)
	{
		sem_wait(d->global_stuffed_sem);
		i++;
	}
	sem_wait(d->local_stuffed_var_sem);
	*d->are_philos_stuffed = true;
	sem_post(d->local_stuffed_var_sem);
	return (NULL);
}

// This only monitors the global stop semaphore
// It doesn't post because the supervisor posts once for each philo anyway
void	*philo_stop_monitor(void *p)
{
	t_philo_stop_monitor	*d;

	d = p;
	sem_wait(d->global_stop_sem);
	sem_wait(d->local_stop_var_sem);
	*d->local_stop = true;
	sem_post(d->local_stop_var_sem);
}

//	Philo process
//
// 1. Prepare local sem
// 2. Prepare local help thread
// 3. Post ready
// 4. Wait start
// 5. Run routine
void	philo_process(...)
{
	
}

void	philo_routine(...)
{
	
}
