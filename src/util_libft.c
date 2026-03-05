/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:46:37 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/05 11:25:59 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_util.h"

// Return difference in usec
// If the subtraction results in integer overflow, behavior is undefined
int	ft_time_sub(struct timeval val, struct timeval sub)
{
	return (1000000 * (val.tv_sec - sub.tv_sec) + (val.tv_usec - sub.tv_usec));
}

// Add microseconds to time
struct timeval	ft_time_add(struct timeval time, unsigned int usec)
{
	time.tv_sec += usec / 1000000;
	time.tv_usec += usec % 1000000;
	if (time.tv_usec > 1000000)
	{
		time.tv_sec++;
		time.tv_usec -= 1000000;
	}
	return (time);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}
