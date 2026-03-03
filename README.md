*This project has been created as part of the 42 curriculum by rapohlen.*

### [Subject](https://cdn.intra.42.fr/pdf/pdf/184896/en.subject.pdf)

### Description

*"I never thought philosophy would be so deadly"*

In this project, we learn about multi-threading and mutexes. The project is about simulating a simple self-playing game where a certain number of "philosophers" take turns "thinking, eating, and sleeping". The interesting part is that philosophers cannot all eat at the same time, as they are limited by a certain amount of "forks" with which they eat.

Each philosopher is simulated by a different thread, so philosophers can act separately and independently. They act in parallel, as such we need to be careful to avoid data races (several threads trying to access the same value in memory at the same time).

In the base version, philosophers are simulated as threads in the same process. In the bonus version, they are simulated as completely separate processes.

Params:

```bash
./philo (number_of_philosophers) (time_to_die) (time_to_eat) (time_to_sleep) [number_of_times_each_philosopher_must_eat]
time_to_die     if philo has not started eating in so much time, it dies and the simulation stops
time_to_eat     time for a philo to eat (it will hold 2 forks)
time_to_sleep   time for a philo to sleep after eating
```

A philosopher has to hold 2 forks to eat. There are as many forks as philosophers. Philosophers sit at a round table.

In the base version, each philosopher has a fork to its left and right (if there is only one philosopher, there is only one fork). Philosopher N's left fork is philosopher N+1's right fork. Forks are represented as mutexes in the code.

In the bonus version, all forks are in a pile at the center of the table, all philosophers have access to all forks. Forks are represented as semaphores in the code.

### Instructions

In `philo` or `philo_bonus`:

1. Run make

```bash
make
```

2. Run philosophers

```bash
./philo 2 1000 200 600 10
```

### Resources

```bash
man pthread create
man pthread join
man sem open
man sem close
man sem unlink
```

[`man pthread_mutex_init`](https://man7.org/linux/man-pages/man3/pthread_mutex_init.3p.html)

[`man pthread_mutex_destroy`](https://man7.org/linux/man-pages/man3/pthread_mutex_destroy.3p.html)

[`man pthread_mutex_lock`](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)

AI was used as a helper to learn about multi-threading, semaphores and best coding practices (e.g error management).
