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
		sem_post(d->sem.global.critical_error);
		error_out(d);
	}
	d->sem.philo.stop_var =  create_sem(local_sem_name, 1);
	free(local_sem_name);
	if (d->sem.philo.stop_var == SEM_FAILED)
	{
		write(2, PHILO_ERR_SEM, sizeof(PHILO_ERR_SEM) - 1);
		sem_post(d->sem.global.critical_error);
		error_out(d);
	}
}

static void	prepare_monitor_data(t_prog *d, t_philo_stop_monitor *monitor_data)
{
	monitor_data->global_stop_sem = d->sem.global.stop;
	monitor_data->local_stop_var_sem = d->sem.philo.stop_var;
	monitor_data->local_stop
}

static void	launch_thread(t_prog *d)
{
	if (pthread_create(&d->thread.philo.stop_monitor, NULL, philo_stop_monitor,
				);
	if ()
}

void	philo_process(t_prog *d)
{
	t_philo_stop_monitor monitor_data;

	create_local_sem(d);
	prepare_monitor_data(d, &monitor_data);
	// thread
	sem_wait(d->sem.shared.start);
	philo_routine(d);
	pthread_join();
}

void	philo_routine(t_main *main)
{
	t_philo	philo;

	init_philo();
	wait_start();
	philo_loop();
	cleanup_philo();
}

void	init_supervisor(t_supervisor *supervisor, const t_main *main)
{
	supervisor->num_philos = main->num_philos;
	supervisor->rules = main->rules;
	supervisor->time = main->time;
	supervisor->sem.global = main->global_sem;
}

void	supervisor_routine(t_main *main)
{
	t_supervisor	supervisor;

	init_supervisor(&supervisor, main);
	launch_start();
	supervisor_loop();
	cleanup_supervisor();
}

void	do_forks(t_main *main)
{
}

void	check_sems_available(t_main *main)
{
}

void	init_sem(t_main *main)
{
}

void	get_args(t_main *main)
{
}

void	init_main(t_main *main)
{
}

int	main(int ac, char **av)
{
	t_main	main;

	if (ac != 5 && ac != 6)
	{
		print_usage();
		return (0);
	}
	init_main(&main);
	get_args(&main);
	init_sem(&main);
	check_sems_avail(&main);
	do_forks(&main);
	cleanup_main(&main);
	return (0);
}













