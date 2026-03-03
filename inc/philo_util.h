/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 14:58:24 by rapohlen          #+#    #+#             */
/*   Updated: 2026/03/03 14:10:48 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_UTIL_H
# define PHILO_UTIL_H

# include <sys/time.h>	// struct timeval definition
# include <string.h>	// size_t definition
# include <stdlib.h>	// malloc

# define BASE2		"01"
# define BASE8		"01234567"
# define BASE10		"0123456789"
# define BASE16		"0123456789abcdef"

// FT_ATOX MACROS
// 17 Unsigned / Signed
# define ATOX_U		0x00010000
# define ATOX_S		0
// 18 Ignore base case
# define ATOX_CASE	0x00020000
// 19 Allow spaces
# define ATOX_SPA	0x00040000
// 20 Allow plus
# define ATOX_PLUS	0x00080000
// 21 Allow multi-sign
# define ATOX_MULT	0x00100000
// 22 Allow base prefix
# define ATOX_PREF	0x00200000
// 23 Allow preceding zeros
# define ATOX_ZERO	0x00400000
// 24 Allow absent number
# define ATOX_ABS	0x00800000
// 25 Allow trailing characters
# define ATOX_TR	0x01000000
// Allow all
# define ATOX_LAX	0x01fe0000
// Forbid all
# define ATOX_STRICT	0

typedef struct s_atox
{
	char			*str;
	char			*base;
	char			*base_i;
	unsigned char	baselen;
	unsigned char	*var;
	unsigned short	varlen;
	int				neg;
	char			has_digit;
	char			is_signed;
	char			ignore_case;
	char			skip_spaces;
	char			skip_plus;
	char			multiple_signs;
	char			skip_prefix;
	char			skip_zeros;
	char			nonum_ok;
	char			allow_extra;
}	t_atox;

// Util
int				ft_time_sub(struct timeval val, struct timeval sub);
struct timeval	ft_time_add(struct timeval time, unsigned int usec);
int				ft_atox(char *str, char *base, void *var, int params);
char			*ft_itoa(int n);
char			*ft_strjoin(const char *s1, const char *s2);

// Used in atox
int				ft_atox_convert(t_atox *d, int *i);
void			*ft_memset(void *s, int c, size_t n);
char			*ft_strchr(char *s, char c);
char			*ft_strchr_case(char *s, char c);
int				ft_isspace(char c);
size_t			ft_strlen(const char *s);
int				ft_isupper(char c);
int				ft_islower(char c);

#endif
