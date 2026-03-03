/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_itoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:02:44 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/03 14:02:57 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	itoa_get_len(long n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	itoa_recurse(char *new, long n, int i)
{
	if (n < 0)
	{
		new[0] = '-';
		n = -n;
	}
	if (n > 9)
		itoa_recurse(new, n / 10, i - 1);
	new[i] = n % 10 + '0';
}

char	*ft_itoa(int n)
{
	char	*new;
	int		len;

	len = itoa_get_len(n);
	new = malloc(len + 1);
	if (!new)
		return (new);
	itoa_recurse(new, n, len - 1);
	new[len] = 0;
	return (new);
}
