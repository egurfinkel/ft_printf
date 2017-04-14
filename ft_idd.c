/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egurfink <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 21:56:19 by egurfink          #+#    #+#             */
/*   Updated: 2017/04/13 21:56:20 by egurfink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t		get_int(int len, va_list v_lst)
{
	if (len == 1)
		return (char)(va_arg(v_lst, int));
	else if (len == 2)
		return (short)(va_arg(v_lst, int));
	else if (len == 3)
		return (va_arg(v_lst, long));
	else if (len == 4)
		return (va_arg(v_lst, long long int));
	else if (len == 5)
		return (va_arg(v_lst, size_t));
	else if (len == 6)
		return (va_arg(v_lst, intmax_t));
	else
		return (va_arg(v_lst, int));
}

void			int_magic(t_spc *a, int *count, intmax_t i, const char *s)
{
	if (a->wd >= a->prc && a->prc > ft_countnum(i))
		a->wd -= a->prc;
	else
		a->wd -= (ft_strlen(s));
	(!a->neg && a->f[2] == 1) ? (a->wd--) : 0;
	(((size_t)a->prc > ft_strlen(s)) && (a->prc != -1))
	? (a->prc -= ft_strlen(s))
	: (a->prc = 0);
	(a->f[4] == 1 && a->f[2] != 1 && !a->neg && ++(*count))
	? ft_putchar(' ') : 0;
	if (a->prc <= 0 && a->f[0])
	{
		if (a->f[2] == 1 && !a->neg && ++(*count))
			ft_putchar('+');
		else if (a->neg && a->wand++ == 0 && ++(*count))
			ft_putchar('-');
		while (a->wd-- > 0 && ++(*count))
			ft_putchar('0');
	}
}

void			to_int(t_spc *a, va_list v_lst, int *count)
{
	intmax_t	i;
	char		*s;

	i = get_int(a->ln, v_lst);
	(i < 0) ? (a->neg = 1) : 0;
	a->neg ? (i *= -1) : 0;
	(a->prc <= ft_countnum(i) && a->prc != -1) ? a->f[0] = 0 : 0;
	(a->neg || (a->f[4] && !a->f[2])) ? (a->wd--) : 0;
	s = ft_itoa_base(i, 10);
	(i == 0 && a->prc == 0) ? (s = "") : 0;
	!ft_strcmp(s, "-9223372036854775808") ? (a->wand = 1) : 0;
	(a->wd < a->prc) ? a->wd = 0 : 0;
	int_magic(a, count, i, s);
	while (a->wd-- > 0 && ++(*count))
		ft_putchar(' ');
	(a->f[2] == 1 && !a->neg && !a->f[0] && ++(*count)) ? ft_putchar('+') : 0;
	(a->neg && !a->f[0] && a->wand++ == 0 && ++(*count)) ? ft_putchar('-') : 0;
	(a->neg && !a->wand && ++(*count)) ? ft_putchar('-') : 0;
	while (a->prc-- > 0 && ++(*count))
		ft_putchar('0');
	i = 0;
	while (s[i] && ++(*count))
		ft_putchar(s[i++]);
}

void			int_minus_magic(t_spc *a, intmax_t i, const char *s)
{
	if (a->wd >= a->prc && a->prc > ft_countnum(i))
		a->wd -= a->prc;
	else
		a->wd -= ft_strlen(s);
}

void			to_int_minus(t_spc *a, va_list v_lst, int *count)
{
	intmax_t	i;
	char		*s;

	i = get_int(a->ln, v_lst);
	(i < 0) ? (a->neg = 1) : 0;
	a->neg ? (i *= -1) : 0;
	(a->neg || (a->f[4] && !a->f[2])) ? a->wd-- : 0;
	(a->wd < a->prc) ? a->wd = 0 : 0;
	s = ft_itoa_base(i, 10);
	(i == 0 && a->prc == 0) ? (s = "") : 0;
	int_minus_magic(a, i, s);
	(!a->neg && a->f[2] == 1) ? (a->wd--) : 0;
	((size_t)a->prc > ft_strlen(s)) ? (a->prc -= ft_strlen(s)) : (a->prc = 0);
	i = 0;
	(a->f[4] == 1 && a->f[2] != 1 && !a->neg && ++(*count))
	? ft_putchar(' ') : 0;
	(a->f[2] == 1 && !a->neg && ++(*count)) ? ft_putchar('+') : 0;
	(a->neg && ++(*count)) ? ft_putchar('-') : 0;
	while (a->prc-- > 0 && ++(*count))
		ft_putchar('0');
	while (s[i] && ++(*count))
		ft_putchar(s[i++]);
	while (a->wd-- > 0 && ++(*count))
		ft_putchar(' ');
}
