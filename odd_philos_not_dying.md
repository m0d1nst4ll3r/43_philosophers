Try ./philo 79 599 200 200 100

Sometimes you get deaths, sometimes you don't.

This might seem like a mistake, but it's not. There's a way to optimize the way philos eat so that they stay alive with odd numbers.

Theoretically, ./philo 5 560 200 200 SHOULD be able to stay alive forever

	0		200		400		600
1	eat		sleep	wait	die
2	eat		sleep	eat
3	wait	eat		sleep
4	wait	eat		sleep
5	wait	wait	eat

1 should die between eat + sleep + wait + eat but if the wait is fast enough (eat + sleep was 400, so wait just needs to be 150 for example), then it's fine.
How to do that? Incur a delay before 1 starts eating the 1st time. He starts eating later than everyone else, but can start eating the 2nd time a bit sooner.
This will incur a delay on everyone, but that delay is fine if they swap between being a late eater and early eater.

	0		50		200		250		400		450		600		650		800		850		1000	1050
1	wait	eat		-		sleep	-		wait	eat		-		sleep	-		wait	eat
2	eat		-		sleep	-		wait	eat		-		sleep	-		wait	eat		-
3	wait	-		eat		-		sleep	-		wait	eat		-		sleep	-		wait
4	wait	-		-		eat		-		sleep	-		wait	eat		-		sleep	-
5	wait	-		-		-		eat		-		sleep	-		wait	eat		-		sleep

The cycle isn't eat sleep eat sleep it's wait, eat, sleep, wait, eat, sleep


With some philos being able to eat instantly, and one (only ONE) philo having to wait before eating the very first time around, they can optimize their cycles

In this example 1 waits 50 ms, and this works with 560, but once the cycle is set, every philo eats every 450ms

It's possible to optimize further, if 1 waits more for his 1st eat

If 1 waits 100ms, he can eat at 600 next, therefore taking 500ms

But the rest will have to wait 50 more ms to eat, raising their wait from 450ms to 500ms

This is because in this case there are 5 forks for 5 philosophers, they need 2 forks to eat for 200 ms, therefore 2.5 philos on average can eat every cycle for a total time of 500ms

Improved cycles:

	0		100		200		300		400		500		600		700		800		900		1000	1100
1	wait	eat		-		sleep	-		wait	eat		-		sleep	-		wait	eat
2	eat		-		sleep	-		wait	eat		-		sleep	-		wait	eat		-
3	wait	-		eat		-		sleep	-		wait	eat		-		sleep	-		wait
4	wait	-		-		eat		-		sleep	-		wait	eat		-		sleep	-
5	wait	-		-		-		eat		-		sleep	-		wait	eat		-		sleep

1 wait 100, then 500, then 500
2 waits 0, then 500, then 500
3 waits 200, then 500, then 500
4 waits 300, then 500...
5 waits 400, then 500...

Note that I *did not* optimize my philos to strategize this way for odd numbers, although this would be a simple quick fix. But due to small delays, some philos *do* wait a couple ms before eating, therefore making 599, 598, etc... possible.

This example does not work for the base version, because 2 and 1 couldn't eat so close to each other (1's right fork is still locked). We just have to move the numbers around:

	0		100		200		300		400		500		600		700		800		900		1000	1100
1	eat		-		sleep	-		wait	eat		-		sleep	-		wait	eat		-
2	wait	-		-		eat		-		sleep	-		wait	eat		-		sleep	-
3	wait	eat		-		sleep	-		wait	eat		-		sleep	-		wait	eat
4	wait	-		-		-		eat		-		sleep	-		wait	eat		-		sleep
5	wait	-		eat		-		sleep	-		wait	eat		-		sleep	-		wait
