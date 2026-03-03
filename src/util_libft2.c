/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_libft2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:46:46 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/03 12:48:17 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_util.h"

char	*ft_strchr_case(char *s, char c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == c
			|| (ft_islower(s[i]) && s[i] - 32 == c)
			|| (ft_isupper(s[i]) && s[i] + 32 == c))
			return (s + i);
		i++;
	}
	if (s[i] == c)
		return (s + i);
	return (NULL);
}

void	*ft_memset(void *s, int c, size_t n)
{
	char	*array;
	size_t	i;

	if (!s)
		return (s);
	i = 0;
	array = (char *)s;
	while (i < n)
	{
		array[i] = (char)c;
		i++;
	}
	return (s);
}

int	ft_isupper(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int	ft_islower(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}
