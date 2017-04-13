/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egurfink <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:54:48 by egurfink          #+#    #+#             */
/*   Updated: 2017/03/25 16:16:18 by egurfink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int 			countlen(intmax_t n)
{
	int len;

	len = 0;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

unsigned int 	w_base(t_spec *a)
{
	if (a->type == 'o' || a->type == 'O')
		return (8);
	if (a->type == 'x' || a->type == 'X' || a->type == 'p')
		return (16);
	else
		return(10);
}

int 			if_width(const char *s)
{
	if (*s != '0' && ft_isdigit(*s))
		return (1);
	return (0);
}

int 			if_length(const char *s)
{
	if (ft_strncmp("hh", s, 2) == 0)
		return (1);
	if (ft_strncmp("h", s, 1) == 0)
		return (1);
	if (ft_strncmp("ll", s, 2) == 0)
		return (1);
	if (ft_strncmp("l", s, 1) == 0)
		return (1);
	if (ft_strncmp("z", s, 1) == 0)
		return (1);
	if (ft_strncmp("j", s, 1) == 0)
		return (1);
	return (0);
}

int 			if_precision(const char *s)
{
	if (*s == '.')
		return (1);
	return (0);
}

int 			if_flag(const char ch)
{
	if (ch == '+' || ch == '-' || ch == '0' || ch == ' ' || ch == '#')
		return (1);
	return (0);
}

void			struct_init(t_spec **str)
{
	(*str) = (t_spec*)malloc(sizeof(t_spec));
	(*str)->wd = -1;
	(*str)->prc = -1;
	(*str)->f[0] = 0;
	(*str)->f[1] = 0;
	(*str)->f[2] = 0;
	(*str)->f[3] = 0;
	(*str)->f[4] = 0;
	(*str)->ln = -1;
	(*str)->type = '\0';
	(*str)->h = 0;
	(*str)->l = 0;
	(*str)->wand = 0;
}

void			tmp_struct_init(t_var **str)
{
	(*str) = (t_var*)malloc(sizeof(t_var));
	(*str)->w = 0;
	(*str)->p = 0;
	(*str)->f = 0;
	(*str)->l = 0;
}

int 			find_flag(const char *s, t_spec *a)
{
	if (*s == '0')
		a->f[0] = 1;
	else if (*s == '-')
		a->f[1] = 1;
	else if (*s == '+')
		a->f[2] = 1;
	else if (*s == '#')
		a->f[3] = 1;
	else if (*s == ' ')
		a->f[4] = 1;
	return (1);
}

int				find_width(const char *s, t_spec *a)
{
	a->wd = ft_atoi(s);
	return (countlen(a->wd));
}

int				find_precision(const char *s, t_spec *a)
{
	int 		prec;

	prec = 1;
	s++;
	if (*s != '-' && *s != '+')
	{
		a->prc = ft_atoi((char*)s);
		prec += countlen(a->prc);
		if (*s == '0')
			prec++;
	}
	return (prec);
}

void			find_lh(const char *s, t_spec *a)
{
	int			i;

	i = 0;
	if (a->h == 0 && a->l == 0)
	{
		while (s[i] && s[i] != '%')
		{
			if ((a->h > 0 || a->l > 0) && s[i] == ' ')
				a->f[4] = 1;
			(s[i] == 'h') ? a->h++ : 0;
			(s[i] == 'l') ? a->l++ : 0;
			i++;
		}
	}
}

int				find_length(const char *s, t_spec *a)
{
	find_lh(s, a);
	if (a->h > 0 && a->ln < 2)
	{
		a->ln = ((a->h % 2 == 0) ? 1 : 2);
		a->h = 0;
	}
	else if (a->l > 0 && a->ln < 4)
	{
		a->ln = ((a->l % 2 == 0) ? 3 : 4);
		a->l = 0;
	}
	else if (ft_strncmp("z", s, 1) == 0 && a->ln < 5)
		a->ln = 5;
	else if (ft_strncmp("j", s, 1) == 0 && a->ln < 6)
		a->ln = 6;
	if (a->ln == 1 || a->ln == 3)
		return (2);
	return (1);
}

char 			get_char(va_list v_lst)
{
	return ((char)va_arg(v_lst, int));
}

char 			*get_string(va_list v_lst)
{
	return (va_arg(v_lst, char*));
}

intmax_t 		get_int(int len, va_list v_lst)
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

uintmax_t		get_uint(int len, va_list v_lst)
{
	if (len == 1)
		return (unsigned char)(va_arg(v_lst, unsigned int));
	else if (len == 2)
		return (unsigned short)(va_arg(v_lst, unsigned int));
	else if (len == 3)
		return (va_arg(v_lst, unsigned long));
	else if (len == 4)
		return (va_arg(v_lst, unsigned long long int));
	else if (len == 5)
		return (va_arg(v_lst, size_t));
	else if (len == 6)
		return (va_arg(v_lst, uintmax_t));
	else
		return (va_arg(v_lst, unsigned int));
}

uintmax_t		get_octal(int len, va_list v_lst)
{
	if (len == 1)
		return (unsigned char)(va_arg(v_lst, unsigned int));
	else if (len == 2)
		return (unsigned short)(va_arg(v_lst, unsigned int));
	else if (len == 3)
		return (va_arg(v_lst, unsigned long));
	else if (len == 4)
		return (va_arg(v_lst, unsigned long long int));
	else if (len == 5)
		return (va_arg(v_lst, size_t));
	else if (len == 6)
		return (va_arg(v_lst, uintmax_t));
	else
		return (va_arg(v_lst, unsigned int));
}

uintmax_t 		get_hex(int len, va_list v_lst)
{
	if (len == 1)
		return (unsigned char)(va_arg(v_lst, unsigned int));
	else if (len == 2)
		return (unsigned short)(va_arg(v_lst, unsigned int));
	else if (len == 3)
		return (va_arg(v_lst, unsigned long));
	else if (len == 4)
		return (va_arg(v_lst, unsigned long long int));
	else if (len == 5)
		return (va_arg(v_lst, size_t));
	else if (len == 6)
		return (va_arg(v_lst, uintmax_t));
	else
		return (va_arg(v_lst, unsigned int));
}

char			set_symb(const t_spec *a)
{
	char symb;

	if (a->f[0])
		symb = '0';
	else
		symb = ' ';
	return symb;
}

void			else_char(int *count, char *ch)
{
		write(1, ch, 1);
		(*count)++;
	}

void			to_char(t_spec *a, va_list v_lst, int *count, int flag)
{
	char		ch;
	char		symb;

	flag ? ch = get_char(v_lst) : (ch = a->type);
	symb = set_symb(a);
	if (a->wd)
	{
		if (a->f[1])
		{
			(*count)++;
			write(1, &ch, 1);
			while (--a->wd > 0 && ++(*count))
				write(1, " ", 1);
		}
		else
		{
			while (--a->wd > 0 && ++(*count))
				write(1, &symb, 1);
			write(1, &ch, 1);
			(*count)++;
		}
	}
	else
		else_char(count, &ch);
}

void			to_char_big(t_spec *a, va_list v_lst, int *count, int flag)
{
	to_char(a, v_lst, count, flag);
}

void			string_magic(t_spec *a, int *count, const char *s, int i)
{
	if (s)
	{
		if (a->f[1] == 0 && a->f[0] == 1)
		{
			while (a->wd-- > 0 && ++(*count))
				write(1, "0", 1);
		} else
		{
			while (a->wd-- > 0 && ++(*count))
				write(1, " ", 1);
		}
		if (a->prc != -1 && (size_t) a->prc < ft_strlen(s))
		{
			while (i < a->prc && ++(*count))
				ft_putchar(s[i++]);
		} else
		{
			while (s[i] && ++(*count))
				ft_putchar(s[i++]);
		}
	}
}

void 			to_string(t_spec *a, va_list v_lst, int *count)
{
	char 	*s;
	int 	i;

	i = 0;
	s = get_string(v_lst);
	(!s) ? (s = "(null)") : 0;
	(a->prc != -1 && (size_t) a->prc < ft_strlen(s))
	? (a->wd -= a->prc) : (a->wd -= ft_strlen(s));
	string_magic(a, count, s, i);
}

void			to_string_big(t_spec *a, va_list v_lst, int *count)
{
	to_string(a, v_lst, count);
}

void			string_minus_magic(t_spec *a, int *count, const char *s, int i)
{
	if (s)
	{
		(a->prc != -1 && (size_t) a->prc < ft_strlen(s))
		? (a->wd -= a->prc) : (a->wd -= ft_strlen(s));
		if (a->prc != -1 && (size_t) a->prc < ft_strlen(s))
		{
			while (i < a->prc && ++(*count))
				ft_putchar(s[i++]);
		}
		else
		{
			while (s[i] && ++(*count))
				ft_putchar(s[i++]);
		}
		if (a->f[1] == 0 && a->f[0] == 1)
		{
			while (a->wd-- > 0 && ++(*count))
				write(1, "0", 1);
		}
		else
		{
			while (a->wd-- > 0 && ++(*count))
				write(1, " ", 1);
		}
	}
}

void			to_string_minus(t_spec *a, va_list v_lst, int *count)
{
	char 	*s;
	int 	i;

	i = 0;
	s = get_string(v_lst);
	(!s) ? (s = "(null)") : 0;
	string_minus_magic(a, count, s, i);
}

void			to_string_minus_big(t_spec *a, va_list v_lst, int *count)
{
	to_string_minus(a, v_lst, count);
}

void
int_magic(t_spec *a, int *count, intmax_t i, const char *s)
{
	int 	neg;

	(i < 0) ? (neg = 1) : (neg = 0);
	if (a->wd >= a->prc && a->prc > countlen(i))
		a->wd -= a->prc;
	else
		a->wd -= (ft_strlen(s));
	(!neg && a->f[2] == 1) ? (a->wd--) : 0;
	(((size_t)a->prc > ft_strlen(s)) && (a->prc != -1))
	? (a->prc -= ft_strlen(s)) : (a->prc = 0);
	(a->f[4] == 1 && a->f[2] != 1 && !neg && ++(*count)) ? ft_putchar(' ') : 0;
	if (a->prc <= 0 && a->f[0])
	{
		if (a->f[2] == 1 && !neg && ++(*count))
			ft_putchar('+');
		else if (neg && a->wand++ == 0 && ++(*count))
			ft_putchar('-');
		while (a->wd-- > 0 && ++(*count))
			ft_putchar('0');
	}
}

void			to_int(t_spec *a, va_list v_lst, int *count)
{
	intmax_t	i;
	char		*s;
	int 		neg;

	i = get_int(a->ln, v_lst);
	(i < 0) ? (neg = 1) : (neg = 0);
	neg ? (i *= -1) : 0;
	(a->prc <= countlen(i) && a->prc != -1) ? a->f[0] = 0 : 0;
	(neg || (a->f[4] && !a->f[2])) ? (a->wd--) : 0;
	(i == 0 && a->prc == 0) ? (s = "") : (s = ft_itoa_base(i, 10));
	!ft_strcmp(s, "-9223372036854775808") ? (a->wand = 1) : (a->wand = 0);
	(a->wd < a->prc) ? a->wd = 0 : 0;
	int_magic(a, count, i, s);
	while (a->wd-- > 0 && ++(*count))
		ft_putchar(' ');
	(a->f[2] == 1 && !neg && !a->f[0] && ++(*count)) ? ft_putchar('+') : 0;
	(neg && !a->f[0] && a->wand++ == 0 && ++(*count)) ? ft_putchar('-') : 0;
	(neg && !a->wand && ++(*count)) ? ft_putchar('-') : 0;
	while (a->prc-- > 0 && ++(*count))
		ft_putchar('0');
	i = 0;
	while (s[i] && ++(*count))
		ft_putchar(s[i++]);
}

void			int_minus_magic(t_spec *a, intmax_t i, const char *s)
{
	if (a->wd >= a->prc && a->prc > countlen(i))
		a->wd -= a->prc;
	else
		a->wd -= ft_strlen(s);
}

void			to_int_minus(t_spec *a, va_list v_lst, int *count)
{
	intmax_t	i;
	char		*s;
	int 		neg;

	i = get_int(a->ln, v_lst);
	(i < 0) ? (neg = 1) : (neg = 0);
	neg ? (i *= -1) : 0;
	(neg || (a->f[4] && !a->f[2])) ? a->wd-- : 0;
	(a->wd < a->prc) ? a->wd = 0 : 0;
	(i == 0 && a->prc == 0) ? (s = "") : (s = ft_itoa_base(i, 10));
	int_minus_magic(a, i, s);
	(!neg && a->f[2] == 1) ? (a->wd--) : 0;
	((size_t)a->prc > ft_strlen(s))
	? (a->prc -= ft_strlen(s)) : (a->prc = 0);
	i = 0;
	(a->f[4] == 1 && a->f[2] != 1 && !neg && ++(*count)) ? ft_putchar(' ') : 0;
	(a->f[2] == 1 && !neg && ++(*count)) ? ft_putchar('+') : 0;
	(neg && ++(*count)) ? ft_putchar('-') : 0;
	while (a->prc-- > 0 && ++(*count))
		ft_putchar('0');
	while (s[i] && ++(*count))
		ft_putchar(s[i++]);
	while (a->wd-- > 0 && ++(*count))
		ft_putchar(' ');
}

void			to_uint(t_spec *a, va_list v_lst, int *count)
{
	uintmax_t		ui;
	char			*s;
	char 			symb;

	ui = get_uint(a->ln, v_lst);
	(ui == 0 && a->prc == 0)
	? (s = "") : (s = ft_itoa_base_u(ui, w_base(a)));
	(a->f[0]) ? (symb = '0') : (symb = ' ');
	if (a->wd < a->prc)
		a->wd = 0;
	if (a->wd >= a->prc && a->prc > countlen(ui))
		a->wd -= a->prc;
	else
		a->wd -= (ft_strlen(s));
	(((size_t)a->prc > ft_strlen(s)) && (a->prc != -1))
	? (a->prc -= ft_strlen(s)) : (a->prc = 0);
	while (a->wd-- > 0 && ++(*count))
		ft_putchar(symb);
	while (a->prc-- > 0 && ++(*count))
		ft_putchar('0');
	ui = 0;
	while (s[ui] && ++(*count))
		ft_putchar(s[ui++]);
}

void			to_uint_minus(t_spec *a, va_list v_lst, int *count)
{
	uintmax_t	ui;
	char		*s;

	ui = get_uint(a->ln, v_lst);
	if (a->wd < a->prc)
		a->wd = 0;
	(ui == 0 && a->prc == 0)
	? (s = "") : (s = ft_itoa_base_u(ui, w_base(a)));
	if (a->wd >= a->prc && a->prc > countlen(ui))
		a->wd -= a->prc;
	else
		a->wd -= ft_strlen(s);
	((size_t)a->prc > ft_strlen(s))
	? (a->prc -= ft_strlen(s)) : (a->prc = 0);
	ui = 0;
	while (a->prc-- > 0 && ++(*count))
		ft_putchar('0');
	while (s[ui] && ++(*count))
		ft_putchar(s[ui++]);
	while (a->wd-- > 0 && ++(*count))
		ft_putchar(' ');
}

void			to_hex(t_spec *a, va_list v_lst, int *count)
{
	uintmax_t	x;
	char 		*s;

	x = get_hex(a->ln, v_lst);
	(a->f[3]) ? a->wd -= 2 : 0;
	(x == 0 && a->prc == 0)
	? (s = "") : (s = ft_itoa_base_u(x, w_base(a)));
	if (a->wd < a->prc)
		a->wd = 0;
	if (a->wd >= a->prc && a->prc > countlen(x))
		a->wd -= a->prc;
	else
		a->wd -= (ft_strlen(s));
	(((size_t)a->prc > ft_strlen(s)) && (a->prc != -1))
	? (a->prc -= ft_strlen(s)) : (a->prc = 0);
	while (!a->f[0] && a->wd-- > 0 && ++(*count))
		ft_putchar(' ');
	((a->f[3]) && (x > 0) && (*count += 2)) ? (ft_putstr("0x")) : 0;
	while (a->f[0] && !a->f[1] && a->wd-- > 0 && ++(*count))
		ft_putchar('0');
	while (a->prc-- > 0 && ++(*count))
		ft_putchar('0');
	x = 0;
	while (s[x] && ++(*count))
		ft_putchar((char)ft_tolower((s[x++])));
}

void			to_hex_minus(t_spec *a, va_list v_lst, int *count)
{
	uintmax_t	x;
	char 		*s;

	x = get_hex(a->ln, v_lst);
	(a->f[3]) ? a->wd -= 2 : 0;
	if (a->wd < a->prc)
		a->wd = 0;
	(x == 0 && a->prc == 0)
	? (s = "") : (s = ft_itoa_base_u(x, w_base(a)));
	if (a->wd >= a->prc && a->prc > countlen(x))
		a->wd -= a->prc;
	else
		a->wd -= (ft_strlen(s));
	((a->f[3]) && (x > 0) && (*count += 2)) ? (ft_putstr("0x")) : 0;
	(((size_t)a->prc > ft_strlen(s)) && (a->prc != -1))
	? (a->prc -= ft_strlen(s)) : (a->prc = 0);
	x = 0;
	while (a->prc-- > 0 && ++(*count))
		ft_putchar('0');
	while (s[x] && ++(*count))
		ft_putchar((char)ft_tolower(s[x++]));
	while (a->wd-- > 0 && ++(*count))
		ft_putchar(' ');
}

void			to_hex_big(t_spec *a, va_list v_lst, int *count)
{
	uintmax_t	x;
	char 		*s;

	x = get_hex(a->ln, v_lst);
	(x == 0 && a->prc == 0) ? (s = "") : (s = ft_itoa_base_u(x, w_base(a)));
	(a->f[3]) ? a->wd -= 2 : 0;
	(a->wd < a->prc) ? a->wd = 0 : 0;
	if (a->wd >= a->prc && a->prc > countlen(x))
		a->wd -= a->prc;
	else
		a->wd -= (ft_strlen(s));
	(((size_t)a->prc > ft_strlen(s)) && (a->prc != -1))
	? (a->prc -= ft_strlen(s)) : (a->prc = 0);
	while (!a->f[0] && a->wd-- > 0 && ++(*count))
		ft_putchar(' ');
	((a->f[3]) && (x > 0) && (*count += 2)) ? (ft_putstr("0X")) : 0;
	while (!a->f[0] && a->wd-- > 0 && ++(*count))
		ft_putchar(' ');
	while (a->f[0] && !a->f[1] && a->wd-- > 0 && ++(*count))
		ft_putchar('0');
	while (a->prc-- > 0 && ++(*count))
		ft_putchar('0');
	x = 0;
	while (s[x] && ++(*count))
		ft_putchar(s[x++]);
}

void			to_hex_big_minus(t_spec *a, va_list v_lst, int *count)
{
	uintmax_t	x;
	char 		*s;

	x = get_hex(a->ln, v_lst);
	(a->f[3]) ? a->wd -= 2 : 0;
	if (a->wd < a->prc)
		a->wd = 0;
	(x == 0 && a->prc == 0)
	? (s = "") : (s = ft_itoa_base_u(x, w_base(a)));
	if (a->wd >= a->prc && a->prc > countlen(x))
		a->wd -= a->prc;
	else
		a->wd -= (ft_strlen(s));
	((a->f[3]) && (x > 0) && (*count += 2)) ? (ft_putstr("0X")) : 0;
	(((size_t)a->prc > ft_strlen(s)) && (a->prc != -1))
	? (a->prc -= ft_strlen(s)) : (a->prc = 0);
	x = 0;
	while (a->prc-- > 0 && ++(*count))
		ft_putchar('0');
	while (s[x] && ++(*count))
		ft_putchar(s[x++]);
	while (!a->f[0] && a->wd-- > 0 && ++(*count))
		ft_putchar(' ');
	while (a->f[0] && !a->f[1] && a->wd-- > 0 && ++(*count))
		ft_putchar('0');
}

void			to_octal(t_spec *a, va_list v_lst, int *count)
{
	uintmax_t	o;
	char 		*s;

	o = get_octal(a->ln, v_lst);
	(o > 0 && a->f[3] && a->prc--) ? (a->wd--) : 0;
	if (a->wd < a->prc)
		a->wd = 0;
	(o == 0 && a->prc == 0)
	? s = "" : (s = ft_itoa_base_u(o, w_base(a)));
	(o == 0 && a->f[3]) ? s = "0" : 0;
	if (a->wd >= a->prc && a->prc > countlen(o))
		a->wd -= a->prc;
	else
		a->wd -= (ft_strlen(s));
	(((size_t)a->prc > ft_strlen(s)) && (a->prc != -1))
	? (a->prc -= ft_strlen(s)) : (a->prc = 0);
	while (!a->f[0] && a->wd-- > 0 && ++(*count))
		ft_putchar(' ');
	while (a->f[0] && a->wd-- > 0 && ++(*count))
		ft_putchar('0');
	while (a->prc-- > 0 && ++(*count))
		ft_putchar('0');
	(o > 0 && a->f[3] && ++(*count)) ? ft_putchar('0') : 0;
	o = 0;
	while (s[o] && ++(*count))
		ft_putchar(s[o++]);
}

void			to_octal_minus(t_spec *a, va_list v_lst, int *count)
{
	uintmax_t	o;
	char 		*s;

	o = get_octal(a->ln, v_lst);
	if (a->wd < a->prc)
		a->wd = 0;
	(o == 0 && a->prc == 0)
	? (s = "") : (s = ft_itoa_base_u(o, w_base(a)));
	(o == 0 && a->f[3] && ++(*count)) ? s = "0" : 0;
	(a->f[3]) ? a->wd-- : 0;
	if (a->wd >= a->prc && a->prc > countlen(o))
		a->wd -= a->prc;
	else
		a->wd -= (ft_strlen(s));
	(((size_t)a->prc > ft_strlen(s)) && (a->prc != -1))
	? (a->prc -= ft_strlen(s)) : (a->prc = 0);
	(o > 0 && a->f[3] && ++(*count)) ? ft_putchar('0') : 0;
	o = 0;
	while (a->prc-- > 0 && ++(*count))
		ft_putchar('0');
	while (s[o] && ++(*count))
		ft_putchar(s[o++]);
	while (a->wd-- > 0 && ++(*count))
		ft_putchar(' ');
}

void			to_pointer(t_spec *a, va_list v_lst, int *count)
{
	uintmax_t	p;
	char 		*s;

	p = va_arg(v_lst, unsigned long);
	(p == 0 && a->prc == 0)
	? (s = "") : (s = ft_itoa_base_u(p, w_base(a)));
	(a->wd < a->prc) ? a->wd = 0 : 0;
	if (a->wd >= a->prc && a->prc > countlen(p))
		a->wd -= a->prc;
	else
		a->wd -= (ft_strlen(s));
	(((size_t)a->prc > ft_strlen(s)) && (a->prc != -1))
	? (a->prc -= ft_strlen(s)) : (a->prc = 0);
	(*count) += 2;
	a->wd -= 2;
	while (!a->f[0] && a->wd-- > 0 && ++(*count))
		ft_putchar(' ');
	while (a->f[0] && a->wd-- > 0 && ++(*count))
		ft_putchar('0');
	ft_putstr("0x");
	while (a->prc-- > 0 && ++(*count))
		ft_putchar('0');
	p = 0;
	while (s[p] && ++(*count))
		ft_putchar((char)ft_tolower((s[p++])));
}

void			to_pointer_minus(t_spec *a, va_list v_lst, int *count)
{
	uintmax_t	p;
	char 		*s;

	p = va_arg(v_lst, unsigned long);
	if (a->wd < a->prc)
		a->wd = 0;
	(p == 0 && a->prc == 0)
	? (s = "") : (s = ft_itoa_base_u(p, w_base(a)));
	if (a->wd >= a->prc && a->prc > countlen(p))
		a->wd -= a->prc;
	else
		a->wd -= (ft_strlen(s));
	(((size_t)a->prc > ft_strlen(s)) && (a->prc != -1))
	? (a->prc -= ft_strlen(s)) : (a->prc = 0);
	p = 0;
	ft_putstr("0x");
	while (a->prc-- > 0 && ++(*count))
		ft_putchar('0');
	(*count) += 2;
	a->wd -= 2;
	while (s[p] && ++(*count))
		ft_putchar((char)ft_tolower(s[p++]));
	while (a->wd-- > 0 && ++(*count))
		ft_putchar(' ');
}

void			to_percent(t_spec *a, va_list v_lst, int *count)
{
	to_char(a, v_lst, count, 0);
}

void			call_str(t_spec *spc, va_list v_lst, int *count)
{
	if (spc->type == 'S')
	{
		spc->f[1]
		? (to_string_minus_big(spc, v_lst, count))
		: (to_string_big(spc, v_lst, count));
	}
	else
	{
		spc->f[1]
		? (to_string_minus(spc, v_lst, count))
		: (to_string(spc, v_lst, count));
	}
}

void			call_int(t_spec *spc, va_list v_lst, int *count)
{
	if (spc->type == 'D')
	{
		spc->type = 'd';
		spc->ln = 3;
	}
	spc->f[1]
	? to_int_minus(spc, v_lst, count)
	: to_int(spc, v_lst, count);
}

void			call_pointer(t_spec *spc, va_list v_lst, int *count)
{
		spc->f[1]
		? to_pointer_minus(spc, v_lst, count)
		: to_pointer(spc, v_lst, count);
}

void			call_octal(t_spec *spc, va_list v_lst, int *count)
{
	if (spc->type == 'O')
	{
		spc->type = 'o';
		spc->ln = 3;
	}
	spc->f[1]
	? to_octal_minus(spc, v_lst, count)
	: to_octal(spc, v_lst, count);
}

void			call_uint(t_spec *spc, va_list v_lst, int *count)
{
	if (spc->type == 'U')
	{
		spc->type = 'u';
		spc->ln = 3;
	}
	spc->f[1]
	? to_uint_minus(spc, v_lst, count)
	: to_uint(spc, v_lst, count);
}

void			call_hex(t_spec *spc, va_list v_lst, int *count)
{
	if (spc->type == 'X')
	{
		spc->f[1]
		? to_hex_big_minus(spc, v_lst, count)
		: to_hex_big(spc, v_lst, count);
	}
	else
	{
		spc->f[1]
		? to_hex_minus(spc, v_lst, count)
		: to_hex(spc, v_lst, count);
	}
}

void			call_char(t_spec *spc, va_list v_lst, int *count)
{
	if (spc->type == 'C')
		to_char_big(spc, v_lst, count, 1);
	else
		to_char(spc, v_lst, count, 1);
}

void			for_print(t_spec *spc, va_list v_lst, int *count)
{
	if (spc->type == 'd' || spc->type == 'D' || spc->type == 'i')
		call_int(spc, v_lst, count);
	else if (spc->type == 's' || spc->type == 'S')
		call_str(spc, v_lst, count);
	else if (spc->type == 'p')
		call_pointer(spc, v_lst, count);
	else if (spc->type == 'o' || spc->type == 'O')
		call_octal(spc, v_lst, count);
	else if (spc->type == 'u' || spc->type == 'U')
		call_uint(spc, v_lst, count);
	else if (spc->type == 'x' || spc->type == 'X')
		call_hex(spc, v_lst, count);
	else if (spc->type == 'c' || spc->type == 'C')
		call_char(spc, v_lst, count);
	else
		to_percent(spc, v_lst, count);
}

void			init_struct(t_var **tmp, t_spec **spec)
{
	tmp_struct_init(tmp);
	struct_init(spec);
}

void			free_struct(t_spec **spec, t_var **tmp)
{
	free(*spec);
	free(*tmp);
}

int				ft_magic(const char *str, va_list v_lst, int *count)
{
	int		i;
	t_var	*tmp;
	t_spec 	*spec;

	i = 1;
	init_struct(&tmp, &spec);
	while (str[i] && ((tmp->f = if_flag(str[i])) ||
			(tmp->w = if_width(str + i)) || (tmp->l = if_length(str + i)) ||
			(tmp->p = if_precision(str + i))))
	{
		if (tmp->f == 1)
			i += find_flag(str + i, spec);
		else if (tmp->w == 1)
			i += find_width(str + i, spec);
		else if (tmp->l == 1)
			i += find_length(str + i, spec);
		else if (tmp->p == 1)
			i += find_precision(str + i, spec);
	}
	spec->type = str[i++];
	if (spec->type == '\0')
		return (i - 1);
	for_print(spec, v_lst, count);
	free_struct(&spec, &tmp);
	return (i);
}

int				ft_printf(const char *str, ...)
{
	va_list		ag;
	int			count;
	int			i;

	va_start(ag, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
			i += ft_magic(str + i, ag, &count);
		else
		{
			ft_putchar(str[i++]);
			count++;
		}
	}
	va_end(ag);
	return (count);
}
