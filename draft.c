#include "philo.h"

// Create a semaphore and unlink it right after
// If the semaphore already exists, unlink it
// Return semaphore reference or SEM_FAILED on error (check errno!)
sem_t	*create_sem(char *sem_name, int value)
{
	sem_t	*new_sem;

	sem_unlink(sem_name);
	new_sem = sem_open(sem_name, O_CREAT | O_EXCL, 0600, value);
	if (new_sem == SEM_FAILED)
		return (new_sem);
	sem_unlink(sem_name);
	return (new_sem);
}

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
char	*get_local_sem_name(int philo_id)
{
	char	*sem_name;
	char	*philo_id_str;

	philo_id_str = ft_itoa(philo_id);
	if (!philo_id_str)
		return (NULL);
	sem_name = ft_join(PHILO_LOCAL_SEM_NAME, philo_id_str);
	free(philo_id_str);
	return (sem_name);
}

static bool	create_local_sem(t_prog *d)
{
	char	*local_sem_name;

	local_sem_name = get_local_sem_name(d->philo_id);
	if (!local_sem_name)
	{
		write(2, PHILO_ERR_MALLOC, sizeof(PHILO_ERR_MALLOC) - 1);
		sem_post(d->sem.shared.critical_error);
		error_out(d);
	}
	d->sem.philo.stop_var =  create_sem(local_sem_name, 1);
	free(local_sem_name);
	if (d->sem.philo.stop_var == SEM_FAILED)
	{
		write(2, PHILO_ERR_SEM, sizeof(PHILO_ERR_SEM) - 1);
		sem_post(d->sem.shared.critical_error);
		error_out(d);
	}
}

static void	launch_thread(t_prog *d)
{
	if (pthread_create(&d->thread.philo.stop_monitor;
	if ()
}

void	philo_process(t_prog *d)
{
	// thread
	sem_wait(d->sem.shared.start);
	philo_routine(d);
}

void	philo_routine(t_prog *d)
{
	
}
