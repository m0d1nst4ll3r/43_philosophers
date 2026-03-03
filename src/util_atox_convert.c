/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_atox_convert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:23:19 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/03 12:41:39 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_util.h"

// Convert a value into its negative two's complement representation
// The value is contained in [size] bytes starting at address [var]
static void	negative(const t_atox *d)
{
	int	i;

	i = 0;
	while (i + 1 < d->varlen && !d->var[i])
	{
		d->var[i]--;
		i++;
	}
	d->var[i]--;
	i = 0;
	while (i < d->varlen)
	{
		d->var[i] = ~d->var[i];
		i++;
	}
}

static int	has_non_zero(const t_atox *d)
{
	int	i;

	i = 0;
	while (i + 1 < d->varlen)
	{
		if (d->var[i])
			return (1);
		i++;
	}
	return (0);
}

// Adds a one-byte value [add] to another [size]-bytes value [var]
// Returns 1 if there was any overflow
static int	add(const t_atox *d, unsigned short add)
{
	int				i;

	i = 0;
	while (add && i < d->varlen)
	{
		add = d->var[i] + add;
		d->var[i] = (unsigned char)add;
		add = add >> 8;
		i++;
	}
	if (add
		|| (d->is_signed && i == d->varlen && ((!d->neg && d->var[i - 1] > 127)
				|| (d->neg && (d->var[i - 1] > 128
						|| (d->var[i - 1] == 128 && has_non_zero(d)))))))
		return (1);
	return (0);
}

// Multiplies [size]-bytes [var] by one-byte [mult], byte-by-byte
// Returns 1 if there was any overflow
static int	mult(const t_atox *d, unsigned char mult)
{
	unsigned short	tmp;
	unsigned char	rest;
	int				i;

	i = 0;
	rest = 0;
	while (i < d->varlen)
	{
		tmp = d->var[i] * mult;
		d->var[i] = (unsigned char)(tmp + rest);
		rest = (tmp + rest) >> 8;
		i++;
	}
	if (rest || (d->is_signed && ((!d->neg && d->var[i - 1] > 127)
				|| (d->neg && (d->var[i - 1] > 128
						|| (d->var[i - 1] == 128 && has_non_zero(d)))))))
		return (1);
	return (0);
}

int	ft_atox_convert(t_atox *d, int *i)
{
	if (!d->skip_zeros && d->str[*i] == *d->base && d->str[*i + 1]
		&& ((d->ignore_case && ft_strchr_case(d->base, d->str[*i + 1]))
			|| (!d->ignore_case && ft_strchr(d->base, d->str[*i + 1]))))
		return (1);
	while (d->str[*i])
	{
		if (d->ignore_case)
			d->base_i = ft_strchr_case(d->base, d->str[*i]);
		else
			d->base_i = ft_strchr(d->base, d->str[*i]);
		if (!d->base_i)
			break ;
		if (!d->has_digit)
			d->has_digit = 1;
		if (mult(d, d->baselen) || add(d, d->base_i - d->base))
			return (1);
		(*i)++;
	}
	if ((!d->has_digit && !d->nonum_ok) || (d->str[*i] && !d->allow_extra))
		return (1);
	if (d->neg)
		negative(d);
	return (0);
}
