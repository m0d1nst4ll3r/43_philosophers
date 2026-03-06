## Helgrind data race explanation

Helgrind finds a few *possible* data races in this program. Many of them are false positives and cannot ever data race according to the program's logic. I will track all data race problems here.

The main idea is that all threads (all philo threads + main thread) both write and read to their own `d->stop` boolean value. That value is only ever written or read from within a semaphore lock (`d->sem.global.print`, of value 1). Therefore, no data races are ever possible. Helgrind misses this info because it does not look at the entire logic of the program, it is a per-process monitor that has no access to other processes.

All possible data races helgrind finds have to do with the d->stop value at the core of the sim-stopping logic.

This is the core sim-stopping logic of the program:

1. Lock print sem (acts like a regular mutex)
2. Post stop sem in a loop
3. Wait stop_received in a loop
4. Unlock print sem

On the receiving side:

1. Wait on stop sem
2. Set this thread's d->stop value
3. Post stop_received

As you can see, there is no way the d->stop value is written to outside of a print sem lock. It is only written after a stop sem post (which itself happens after a print sem wait), and before a stop_received post (whose wait is blocking the print sem from being unlocked).

This core logic happens whenever the sim stops:

1. A philo died (death_watcher posts)
2. Philos are stuffed (stuffed_watcher posts)
3. Philo thread/sem creation failed (error_stop_child posts)
4. Forks fail (error_stop_parent posts)

In all but the very last case, the logic is exactly as described (in the last case, not all philo threads have been created, we don't wait for stop_received, but we don't need to because the sim hasn't even started yet and the prog will error_out anyway).

All d->stop reads also happen within a print lock:

1. Any of the 4 philo prints (fork, eat, sleep, think)
2. Stuffed watcher (so it can stop)
3. Any of the stop posts (so it doesn't happen twice) (philo dying, philos are stuffed, philo thread/sem creation fail, fork fail)

Therefore, d->stop cannot be written and read in a data race.

The following possible data races were found with `valgrind --tool=helgrind 2 1000 1 1 5`.

### Possible data race #1 - d->stop value death_watcher vs stop_watcher

==530148== Possible data race during read of size 1 at 0x1FFEFFFC31 by thread #3
==530148== Locks held: none
==530148==    at 0x401BFD: signal_death (sim_philo_routine.c:40)
==530148==    by 0x401BD5: death_watcher_thread (sim_philo_routine.c:70)
==530148==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==530148==    by 0x4910AC2: start_thread (pthread_create.c:442)
==530148==    by 0x49A1A83: clone (clone.S:100)
==530148== 
==530148== This conflicts with a previous write of size 1 by thread #2
==530148== Locks held: none
==530148==    at 0x401B18: stop_watcher_thread (sim_philo_routine.c:81)
==530148==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==530148==    by 0x4910AC2: start_thread (pthread_create.c:442)
==530148==    by 0x49A1A83: clone (clone.S:100)
==530148==  Address 0x1ffefffc31 is on thread #1's stack
==530148==  in frame #5, created by main (main.c:23)

Possible d->stop collision between death_watcher (posts stop sem in a loop, therefore has to test d->stop *within its print lock*) and stop_watcher (writes d->stop after stop post and before a stop_received post, which all happens in a *print lock*). False positive.

### Possible data race #2 - d->stop value stop_watcher vs philo sleep/eat/think/fork

==530449== Possible data race during write of size 1 at 0x1FFEFFFC31 by thread #2
==530449== Locks held: none
==530449==    at 0x401B18: stop_watcher_thread (sim_philo_routine.c:81)
==530449==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==530449==    by 0x4910AC2: start_thread (pthread_create.c:442)
==530449==    by 0x49A1A83: clone (clone.S:100)
==530449== 
==530449== This conflicts with a previous read of size 1 by thread #1
==530449== Locks held: none
==530449==    at 0x4020B0: print_fork (sim_philo_funcs.c:37)
==530449==    by 0x401F76: take_forks (sim_philo_funcs.c:55)
==530449==    by 0x401DCB: p_eat (sim_philo_funcs.c:67)
==530449==    by 0x401992: philo_routine (sim_philo_routine.c:106)
==530449==    by 0x40187C: do_forks (init_do_forks.c:36)
==530449==    by 0x4012C8: main (main.c:35)
==530449==  Address 0x1ffefffc31 is on thread #1's stack
==530449==  in frame #7, created by main (main.c:23)

Possible d->stop collision between stop_watcher and philo print. stop_watcher writes to d->stop *within print lock* as explained above. Philo reads d->stop *within print lock* as evident in the code. False positive.

The error exists with p_sleep, p_eat, p_think too.
