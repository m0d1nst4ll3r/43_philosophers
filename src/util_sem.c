/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_sem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:39:40 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/02 14:10:43 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// If the semaphore already exists, unlink it
// Return semaphore reference or SEM_FAILED on error (check errno!)
// Unlink instantly (will never be reopened)
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
