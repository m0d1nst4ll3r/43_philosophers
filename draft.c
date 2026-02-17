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

bool	is_sem_available(char *sem_name)
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

void	philo_routine(t_prog *d)
{
	wait_start();
	philo_loop();
	cleanup_philo();
}

void	supervisor_routine(t_prog *d)
{
	t_supervisor	supervisor;

	init_supervisor(&supervisor, d);
	launch_start();
	supervisor_loop();
	cleanup_supervisor();
}

void	do_forks(t_prog *d)
{
}

void	check_sems_available(t_prog *d)
{
	int	i;

	if (!is_sem_available(SEM_NAME_START)
		|| !is_sem_available(SEM_NAME_DEAD)
		|| !is_sem_available(SEM_NAME_STOP)
		|| !is_sem_available(SEM_NAME_ERROR))
		error_out(d, ESEMAVAIL);
	i = 0;
	while (i < d->rules.num_philos)
	{
		if (!is_sem_available(d->sem.stuffed[i]))
			error_out(d, ESEMAVAIL);
		i++;
	}
}

void	init_stuffed_sem()
{
}

void	init_sem(t_prog *d)
{
	d->sem.forks = create_sem(SEM_NAME_FORKS, d->rules.num_philos);
	d->sem.print = create_sem(SEM_NAME_PRINT, 1);
	if (d->sem.forks == SEM_FAILED || d->sem.print == SEM_FAILED)
		error_out(d, ESEM);
}

void	get_args(t_prog *d)
{
	d->rules.meals_to_end = 0;
	if (ft_atox(av[1], 0, &d->rules.num_philos,
			sizeof(d->rules.num_philos) | ATOX_U) < 0
		|| ft_atox(av[2], 0, &d->rules.time_to_die,
			sizeof(d->rules.time_to_die) | ATOX_U) < 0
		|| ft_atox(av[3], 0, &d->rules.time_to_eat,
			sizeof(d->rules.time_to_eat) | ATOX_U) < 0
		|| ft_atox(av[4], 0, &d->rules.time_to_sleep,
			sizeof(d->rules.time_to_sleep) | ATOX_U) < 0
		|| (av[5] && ft_atox(av[5], 0, &d->rules.meals_to_end,
				sizeof(d->rules.meals_to_end) | ATOX_U) < 0))
		error_out(d, EARGS);
	if (!d->rules.num_philos)
		error_out(d, EPHILNUM);
}

void	init_prog(t_prog *d)
{
	d->sem.forks = SEM_FAILED;
	d->sem.print = SEM_FAILED;
	d->children_pids = NULL;
	d->sem_name.stuffed = NULL;
}

int	main(int ac, char **av)
{
	t_prog	data;

	if (ac != 5 && ac != 6)
	{
		print_usage();
		return (0);
	}
	init_prog(&data);
	get_args(&data);
	init_sem(&data);
	init_stuffed_sem(&data);
	check_sems_avail(&data);
	do_forks(&data);
	cleanup_data(&data);
	return (0);
}













