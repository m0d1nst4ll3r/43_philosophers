#include <stdlib.h>
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
	char	*test;
}	t_prog;

static void	parent(t_prog *d)
{
	int	i;

	printf("Parent started\n");
	printf("Parent test 1: %p\n", d->test);
	printf("Parent test 2: %s\n", d->test);
	d->test[1] = 'o';
	sleep(1);
	i = 0;
	while (i < 4)
	{
		usleep(500000);
		printf("Parent: Posting semaphore %d\n", i + 1);
		sem_post(d->sem);
		i++;
	}
	printf("Parent test 3: %s\n", d->test);
	waitpid(d->pid, NULL, 0);
	sem_close(d->sem);
	sem_unlink(SEM_NAME);
}

static void	child(t_prog *d)
{
	int	i;

	printf("Child started\n");
	printf("Child test 1: %p\n", d->test);
	printf("Child test 2: %s\n", d->test);
	i = 0;
	while (i < 4)
	{
		sem_wait(d->sem);
		printf("Child: Passed sem %d\n", i + 1);
		i++;
	}
	sem_close(d->sem);
	printf("Child test 3: %s\n", d->test);
}

int	main()
{
	t_prog	d;

	d.test = malloc(5);
	d.test[0] = 't';
	d.test[1] = 'e';
	d.test[2] = 's';
	d.test[3] = 't';
	d.test[4] = 0;
	d.sem = sem_open(SEM_NAME, O_CREAT, 0644, 0);
	d.pid = fork();
	if (d.pid)
		parent(&d);
	else
		child(&d);
	return (0);
}
