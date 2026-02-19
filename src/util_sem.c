/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_sem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:39:40 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/18 18:53:27 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

bool	sem_exists(char *sem_name)
{
	sem_t	*sem;

	sem = sem_open(sem_name, 0);
	if (sem == SEM_FAILED)
		return (false);
	sem_close(sem);
	return (true);
}
