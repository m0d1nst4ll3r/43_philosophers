/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sem_names.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:40:51 by rapohlen          #+#    #+#             */
/*   Updated: 2026/02/18 17:41:20 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*get_fingerprint_time(void)
{
	struct timeval	time;
	char			*fingerprint;
	char			*sec_str;
	char			*usec_str;

	if (gettimeofday(&time, NULL))
		return (NULL);
	sec_str = ft_itoa(time.tv_sec);
	if (!sec_str)
		return (NULL);
	usec_str = ft_itoa(time.tv_usec);
	if (!usec_str)
		return (NULL);
	fingerprint = ft_strjoin(sec_str, usec_str);
	free(sec_str);
	free(usec_str);
	return (fingerprint);
}

static char	*get_fingerprint(void)
{
	char	*fingerprint_time;
	char	*fingerprint_full;

	fingerprint_time = get_fingerprint_time();
	if (!fingerprint_time)
		return (NULL);
	fingerprint_full = ft_strjoin(SEM_NAME_PREFIX, fingerprint_time);
	free(fingerprint_time);
	return (fingerprint_full);
}

static bool	init_sem_stuffed_names(t_prog *d, char *fingerprint)
{
	int	i;
	char	*fingerprint_stuffed;
	char	*id_str;

	fingerprint_stuffed = ft_strjoin(fingerprint, SEM_NAME_SUFFIX_STUFFED);
	if (!fingerprint_stuffed)
		return (false);
	i = 0;
	while (i < d->rules.num_philos)
	{
		id_str = ft_itoa(i);
		if (id_str)
		{
			d->sem.stuffed[i].name = ft_strjoin(fingerprint_stuffed, id_str);
			free(id_str);
		}
		if (!id_str || !d->sem.stuffed[i].name)
		{
			free(fingerprint_stuffed);
			return (false);
		}
		i++;
	}
	free(fingerprint_stuffed);
	return (true);
}

// Using a short, unique fingerprint using gettimeofday to avoid collision
void	init_sem_names(t_prog *d)
{
	int		i;
	char	*fingerprint;

	fingerprint = get_fingerprint();
	if (!fingerprint)
		error_out(d, EMALLOC);
	d->sem.forks.name = ft_strjoin(fingerprint, SEM_NAME_SUFFIX_FORKS);
	d->sem.print.name = ft_strjoin(fingerprint, SEM_NAME_SUFFIX_FORKS);
	d->sem.start.name = ft_strjoin(fingerprint, SEM_NAME_SUFFIX_FORKS);
	d->sem.death.name = ft_strjoin(fingerprint, SEM_NAME_SUFFIX_FORKS);
	d->sem.stop.name = ft_strjoin(fingerprint, SEM_NAME_SUFFIX_FORKS);
	d->sem.error.name = ft_strjoin(fingerprint, SEM_NAME_SUFFIX_FORKS);
	if (!init_sem_stuffed_names())
	{
		free(fingerprint);
		error_out(d, EMALLOC);
	}
	free(fingerprint);
}
