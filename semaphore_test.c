#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>

#define SEM_NAME "philo_sem"

typedef struct s_prog
{
	sem_t	*sem;
	pid_t	pid;
}	t_prog;

static void	parent(t_prog *d)
{
	int	i;

	printf("Parent started\n");
	sleep(1);
	i = 0;
	while (i < 4)
	{
		sleep(1);
		printf("Posting semaphore now!\n");
		sem_post(d->sem);
		i++;
	}
	waitpid(d->pid, NULL, 0);
	sem_close(d->sem);
	sem_unlink(SEM_NAME);
}

static void	child(t_prog *d)
{
	printf("Child started\n");
	sem_wait(d->sem);
	printf("Passed 1 sem\n");
	sem_wait(d->sem);
	printf("Passed 2 sem\n");
	sem_wait(d->sem);
	printf("Passed 3 sem\n");
	sem_wait(d->sem);
	printf("Passed 4 sem\n");
	sem_close(d->sem);
}

int	main()
{
	t_prog	d;

	d.sem = sem_open(SEM_NAME, O_CREAT, 0644, 0);
	d.pid = fork();
	if (d.pid)
		parent(&d);
	else
		child(&d);
	return (0);
}
