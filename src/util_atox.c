/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_atox.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:04:41 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/03 12:41:33 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_util.h"

// Skips ALL preceding characters according to params
static void	skip_preceding(t_atox *d, int *i)
{
	while (d->skip_spaces && ft_isspace(d->str[*i]))
		(*i)++;
	while (d->multiple_signs && ((d->is_signed && d->str[*i] == '-')
			|| (d->skip_plus && d->str[*i] == '+')))
	{
		if (d->str[*i] == '-')
			d->neg = !d->neg;
		(*i)++;
	}
	if ((d->is_signed && d->str[*i] == '-')
		|| (d->skip_plus && d->str[*i] == '+'))
	{
		if (d->str[*i] == '-')
			d->neg = !d->neg;
		(*i)++;
	}
	if (d->skip_prefix && d->str[*i] == '0'
		&& ((d->baselen == 2
				&& (d->str[*i + 1] == 'b' || d->str[*i + 1] == 'B'))
			|| (d->baselen == 16
				&& (d->str[*i + 1] == 'x' || d->str[*i + 1] == 'X'))))
		(*i) += 2;
	else if (d->skip_prefix && d->baselen == 8 && d->str[*i] == '0')
		(*i)++;
}

static void	init_atox(t_atox *d, int params)
{
	d->neg = 0;
	d->has_digit = 0;
	d->is_signed = !(params & ATOX_U);
	d->ignore_case = (params & ATOX_CASE) != 0;
	d->skip_spaces = (params & ATOX_SPA) != 0;
	d->skip_plus = (params & ATOX_PLUS) != 0;
	d->multiple_signs = (params & ATOX_MULT) != 0;
	d->skip_prefix = (params & ATOX_PREF) != 0;
	d->skip_zeros = (params & ATOX_ZERO) != 0;
	d->nonum_ok = (params & ATOX_ABS) != 0;
	d->allow_extra = (params & ATOX_TR) != 0;
}

/*		ft_atox(char *to_convert, char *base, void *to_write, int params)
 *
 * - Converts a string into a signed or unsigned numerical value
 * - Accepts any base (up to 256 length)
 * - Accepts any type (char, intmax_t, custom type... up to 65535 size)
 * - Wards against overflow, no matter the type, signed/unsigned
 * - Returns how far it got into the string (even in case of error)
 * - Flexible, can tell it to behave one way or another when parsing string
 *	(skip spaces or not, allow multiple preceding signs or not, etc...)
 *
 *	Example usage:
 * ft_atox(str, 0, &var, sizeof(var) | ATOX_LAX);
 * ft_atox(str, "0123456789abcdef", &var, sizeof(var) | ATOX_U | ATOX_CASE);
 *
 *	Args:
 * to_convert	string to convert
 * base			base to convert from - if NULL, defaults to base 10
 * to_write		address of variable to write result in
 * params		size of the variable + params (encoded as one value)
 *
 *	Params bits:
 * 1-16
 *	The variable's size in short form (recommend using sizeof())
 * 17
 *	0 (default)	Signed conversion (use ATOX_S to explicit this)
 *	1 ATOX_U	Unsigned conversion (any preceding '-' is invalid)
 * 18
 *	0 (default)	Base case is respected
 *	1 ATOX_CASE	Base case is ignored (in hex base, 'a' and 'A' are both valid)
 * 19
 *	0 (default)	Preceding spaces are invalid
 *	1 ATOX_SPA	Preceding spaces are skipped (as defined by isspace)
 * 20
 *	0 (default)	Preceding '+' is invalid
 *	1 ATOX_PLUS	Preceding '+' is skipped
 * 21
 *	0 (default)	Multiple '+' and '-' are invalid
 *	1 ATOX_MULT	Multiple '+' are skipped and '-' are read (if signed)
 * 22
 *	0 (default)	Preceding base prefix is invalid (e.g "0x" "0b")
 *	1 ATOX_PREF	Preceding base prefix is skipped (depending on base length)
 * 23
 *	0 (default)	Preceding zeros are invalid (unless base prefix)
 *	1 ATOX_ZERO	Preceding zeros are skipped
 * 24
 *	0 (default)	Absent number is invalid
 *	1 ATOX_ABS	Absent number is treated as a 0
 * 25
 *	0 (default)	Trailing non-base characters are invalid
 *	1 ATOX_TR	Trailing non-base characters are skipped
 * The default behavior (no bit set) is to strictly read base digits
 *	(and one preceding '-') as a signed value, and consider any extra
 *	character as invalid. Use ATOX_STRICT to explicit this.
 * Use ATOX_LAX to set all bits (except signed/unsigned) to 1.
 *
 *	Returns:
 * >= 0	Success: String is valid and the variable contains the result
 * < 0	Failure: String is invalid (see reasons), the var may contain anything.
 * - The return value ALWAYS tells you whether or not ft_atox was successful.
 * - The return value TRIES to also tell you how far it got into the string.
 * - Its absolute value will ALMOST ALWAYS be how far it got into the string.
 * - However, if ft_atox failed at the first character in the string, it will
 *		default to returning -1, to indicate an error, even if it didn't get
 *		1 character deep into the string.
 * E.g
 *	"123nonsense" returns (for base 10):
 *		3	if ATOX_TR was set
 *		-3	otherwise
 *	"" returns:
 *		0	if ATOX_ABS was set
 *		-1	otherwise (as there is no other way to indicate an error)
 * This behavior, while remaining imperfect due to technical limitations,
 *	should still prove useful to string-parsing operations.
 *
 *	Possible reasons for failure:
 * 1. The string's value overflowed the desired type's size
 * 2. The string contained invalid characters according to params
 *
 *	Notes:
 * - Arguments are not checked for errors (to save on compute) - be sensible
 * - A preceding '-' is always invalid when reading an unsigned value
 * - Max base length is 255
 * - Max variable size is 65535
*/
int	ft_atox(char *str, char *base, void *var, int params)
{
	t_atox			d;
	int				i;

	if (!base)
		base = BASE10;
	d.baselen = ft_strlen(base);
	d.varlen = (short)params;
	d.str = str;
	d.base = base;
	d.var = var;
	init_atox(&d, params);
	i = 0;
	skip_preceding(&d, &i);
	ft_memset(d.var, 0, d.varlen);
	if (ft_atox_convert(&d, &i))
	{
		if (i)
			return (-i);
		return (-1);
	}
	return (i);
}
