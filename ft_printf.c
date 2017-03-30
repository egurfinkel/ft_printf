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

int 			countlen(int n)
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

//void			free_struct(t_spec *spec, t_var *tmp)
//{
//	free(spec);
//	free(tmp);
//}

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
	(*str)->width = -1;
	(*str)->precision = -1;
	(*str)->flag[0] = 0;
	(*str)->flag[1] = 0;
	(*str)->flag[2] = 0;
	(*str)->flag[3] = 0;
	(*str)->flag[4] = 0;
	(*str)->length = -1;
	(*str)->type = '\0';
	(*str)->h = 0;
	(*str)->l = 0;
}

void			tmp_struct_init(t_var **str)
{
	(*str) = (t_var*)malloc(sizeof(t_var));
	(*str)->width = 0;
	(*str)->precision = 0;
	(*str)->flag = 0;
	(*str)->length = 0;
}

int 			find_flag(const char *s, t_spec *a)
{
	if (*s == '0')
		a->flag[0] = 1;
	else if (*s == '-')
		a->flag[1] = 1;
	else if (*s == '+')
		a->flag[2] = 1;
	else if (*s == '#')
		a->flag[3] = 1;
	else if (*s == ' ')
		a->flag[4] = 1;
	return (1);
}

int				find_width(const char *s, t_spec *a)
{
	a->width = ft_atoi(s);
	return (countlen(a->width));
}

int				find_precision(const char *s, t_spec *a)
{
	int 		prec;

	prec = 1;
	s++;
	if (*s != '-' && *s != '+')
	{
		a->precision = ft_atoi((char*)s);
		prec += countlen(a->precision);
		if (*s == '0')
			prec++;
	}
	return (prec);
}

int				find_length(const char *s, t_spec *a)
{
	if (a->h == 0 && a->l == 0)
	{
		while (*s)
		{
			((*s) == 'h') ? a->h++ : 0;
			((*s) == 'l') ? a->l++ : 0;
			s++;
		}
	}
	if (a->h > 0)
	{
		a->length = (a->h % 2 == 0) ? 1 : 2;
		a->h = 0;
	}
	else if (a->l > 0)
	{
		a->length = (a->l % 2 == 0) ? 3 : 4;
		a->l = 0;
	}
	else if (ft_strncmp("z", s, 1) == 0 && a->length < 5)
		a->length = 5;
	else if (ft_strncmp("j", s, 1) == 0 && a->length < 6)
		a->length = 6;
	if (a->length == 1 || a->length == 3)
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

intmax_t 		get_hex(int len, va_list v_lst)
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

void			to_char(t_spec *a, va_list v_lst, int *count)
{
	char ch;
	char symb;

	ch = get_char(v_lst);
	if (a->flag[0])
		symb = '0';
	else
		symb = ' ';
	if (a->width)
	{
		if (a->flag[1])
		{
			(*count)++;
			write(1, &ch, 1);
			while (--a->width > 0 && ++(*count))
				write(1, " ", 1);
		}
		else
		{
			while (--a->width > 0 && ++(*count))
				write(1, &symb, 1);
			write(1, &ch, 1);
			(*count)++;
		}
	}
	else
	{
		write(1, &ch, 1);
		(*count)++;
	}
}

void 			to_string(t_spec *a, va_list v_lst, int *count)
{
	char 	*s;
	int 	i;

	i = 0;
	s = get_string(v_lst);
	if (s)
	{
		(a->precision != -1 && (size_t) a->precision < ft_strlen(s))
		? (a->width -= a->precision) : (a->width -= ft_strlen(s));
		if (a->flag[1] == 0 && a->flag[0] == 1)
		{
			while (a->width-- > 0 && ++(*count))
				write(1, "0", 1);
		} else
		{
			while (a->width-- > 0 && ++(*count))
				write(1, " ", 1);
		}
		if (a->precision != -1 && (size_t) a->precision < ft_strlen(s))
		{
			while (i < a->precision && ++(*count))
				ft_putchar(s[i++]);
		} else
		{
			while (s[i] && ++(*count))
				ft_putchar(s[i++]);
		}
	}
}

void			to_string_minus(t_spec *a, va_list v_lst, int *count)
{
	char 	*s;
	int 	i;

	i = 0;
	s = get_string(v_lst);
	if (s)
	{
		(a->precision != -1 && (size_t) a->precision < ft_strlen(s))
		? (a->width -= a->precision) : (a->width -= ft_strlen(s));
		if (a->precision != -1 && (size_t) a->precision < ft_strlen(s))
		{
			while (i < a->precision && ++(*count))
				ft_putchar(s[i++]);
		} else
		{
			while (s[i] && ++(*count))
				ft_putchar(s[i++]);
		}
		if (a->flag[1] == 0 && a->flag[0] == 1)
		{
			while (a->width-- > 0 && ++(*count))
				write(1, "0", 1);
		} else
		{
			while (a->width-- > 0 && ++(*count))
				write(1, " ", 1);
		}
	}
}

void			to_int(t_spec *a, va_list v_lst, int *count)
{
	intmax_t	i;
	char		*s;
	int 		neg;

	i = get_int(a->length, v_lst);
	(i < 0) ? (neg = 1) : (neg = 0);
	neg ? (i *= -1) : 0;
	if (neg || (a->flag[4] && !a->flag[2]))
		a->width--;
	(i == 0 && a->precision == 0) ? (s = "") : (s = ft_itoa_base(i, 10));
	if (a->width < a->precision)
		a->width = 0;
	if (a->width >= a->precision && a->precision > countlen(i))
		a->width -= a->precision;
	else
		a->width -= (ft_strlen(s));
	(!neg && a->flag[2] == 1) ? (a->width--) : 0;
	(((size_t)a->precision > ft_strlen(s)) && (a->precision != -1))
	? (a->precision -= ft_strlen(s)) : (a->precision = 0);
	if (a->flag[4] == 1 && a->flag[2] != 1 && !neg && ++(*count))
		ft_putchar(' ');
	if (a->precision <= 0 && a->flag[0])
	{
		while (a->width-- > 0 && ++(*count))
			ft_putchar('0');
	}
	while (a->width-- > 0 && ++(*count))
		ft_putchar(' ');
	if (a->flag[2] == 1 && !neg && ++(*count))
		ft_putchar('+');
	else if (neg && ++(*count))
		ft_putchar('-');
	while (a->precision-- > 0 && ++(*count))
		ft_putchar('0');
	i = 0;
	while (s[i] && ++(*count))
		ft_putchar(s[i++]);
}

void		to_int_minus(t_spec *a, va_list v_lst, int *count)
{
	intmax_t	i;
	char		*s;
	int 		neg;

	i = get_int(a->length, v_lst);
	(i < 0) ? (neg = 1) : (neg = 0);
	neg ? (i *= -1) : 0;
	if (neg || (a->flag[4] && !a->flag[2]))
		a->width--;
	if (a->width < a->precision)
		a->width = 0;
	(i == 0 && a->precision == 0) ? (s = "") : (s = ft_itoa_base(i, 10));
	if (a->width >= a->precision && a->precision > countlen(i))
		a->width -= a->precision;
	else
		a->width -= ft_strlen(s);
	(!neg && a->flag[2] == 1) ? (a->width--) : 0;
	((size_t)a->precision > ft_strlen(s))
	? (a->precision -= ft_strlen(s)) : (a->precision = 0);
	i = 0;
	if (a->flag[4] == 1 && a->flag[2] != 1 && !neg && ++(*count))
		ft_putchar(' ');
	if (a->flag[2] == 1 && !neg && ++(*count))
		ft_putchar('+');
	else if (neg && ++(*count))
		ft_putchar('-');
	while (a->precision-- > 0 && ++(*count))
		ft_putchar('0');
	while (s[i] && ++(*count))
		ft_putchar(s[i++]);
	while (a->width-- > 0 && ++(*count))
		ft_putchar(' ');

}

void				to_uint(t_spec *a, va_list v_lst, int *count)
{
	uintmax_t		ui;
	char			*s;
	char 			symb;

	ui = get_uint(a->length, v_lst);
	(ui == 0 && a->precision == 0)
	? (s = "") : (s = ft_itoa_base_u(ui, w_base(a)));
	(a->flag[0]) ? (symb = '0') : (symb = ' ');
	if (a->width < a->precision)
		a->width = 0;
	if (a->width >= a->precision && a->precision > countlen(ui))
		a->width -= a->precision;
	else
		a->width -= (ft_strlen(s));
	(((size_t)a->precision > ft_strlen(s)) && (a->precision != -1))
	? (a->precision -= ft_strlen(s)) : (a->precision = 0);
	while (a->width-- > 0 && ++(*count))
		ft_putchar(symb);
	while (a->precision-- > 0 && ++(*count))
		ft_putchar('0');
	ui = 0;
	while (s[ui] && ++(*count))
		ft_putchar(s[ui++]);
}

void				to_uint_minus(t_spec *a, va_list v_lst, int *count)
{
	uintmax_t	ui;
	char		*s;

	ui = get_uint(a->length, v_lst);
	if (a->width < a->precision)
		a->width = 0;
	(ui == 0 && a->precision == 0)
	? (s = "") : (s = ft_itoa_base_u(ui, w_base(a)));
	if (a->width >= a->precision && a->precision > countlen(ui))
		a->width -= a->precision;
	else
		a->width -= ft_strlen(s);
	((size_t)a->precision > ft_strlen(s))
	? (a->precision -= ft_strlen(s)) : (a->precision = 0);
	ui = 0;
	while (a->precision-- > 0 && ++(*count))
		ft_putchar('0');
	while (s[ui] && ++(*count))
		ft_putchar(s[ui++]);
	while (a->width-- > 0 && ++(*count))
		ft_putchar(' ');
}

void		to_hex(t_spec *a, va_list v_lst, int *count)
{
	intmax_t	x;
	char 		*s;

	x = get_hex(a->length, v_lst);
	(a->flag[3]) ? a->width -= 2 : 0;
	(x == 0 && a->precision == 0)
	? (s = "") : (s = ft_itoa_base(x, w_base(a)));
	if (a->width < a->precision)
		a->width = 0;
	if (a->width >= a->precision && a->precision > countlen(x))
		a->width -= a->precision;
	else
		a->width -= (ft_strlen(s));
	(((size_t)a->precision > ft_strlen(s)) && (a->precision != -1))
	? (a->precision -= ft_strlen(s)) : (a->precision = 0);
	while (!a->flag[0] && a->width-- > 0 && ++(*count))
		ft_putchar(' ');
	((a->flag[3]) && (x > 0) && (*count += 2)) ? (ft_putstr("0x")) : 0;
	while (a->flag[0] && a->width-- > 0 && ++(*count))
		ft_putchar(' ');
	while (a->precision-- > 0 && ++(*count))
		ft_putchar('0');
	x = 0;
	while (s[x] && ++(*count))
		ft_putchar((char)ft_tolower((s[x++])));
}

void		to_hex_minus(t_spec *a, va_list v_lst, int *count)
{
	intmax_t	x;
	char 		*s;

	x = get_hex(a->length, v_lst);
	(a->flag[3]) ? a->width -= 2 : 0;
	if (a->width < a->precision)
		a->width = 0;
	(x == 0 && a->precision == 0)
	? (s = "") : (s = ft_itoa_base(x, w_base(a)));
	if (a->width >= a->precision && a->precision > countlen(x))
		a->width -= a->precision;
	else
		a->width -= (ft_strlen(s));
	((a->flag[3]) && (x > 0) && (*count += 2)) ? (ft_putstr("0x")) : 0;
	(((size_t)a->precision > ft_strlen(s)) && (a->precision != -1))
	? (a->precision -= ft_strlen(s)) : (a->precision = 0);
	x = 0;
	while (a->precision-- > 0 && ++(*count))
		ft_putchar('0');
	while (s[x] && ++(*count))
		ft_putchar((char)ft_tolower(s[x++]));
	while (a->width-- > 0 && ++(*count))
		ft_putchar(' ');
}

void			to_hex_big(t_spec *a, va_list v_lst, int *count)
{
	intmax_t	x;
	char 		*s;

	x = get_hex(a->length, v_lst);
	(x == 0 && a->precision == 0)
	? (s = "") : (s = ft_itoa_base(x, w_base(a)));
	(a->flag[3]) ? a->width -= 2 : 0;
	if (a->width < a->precision)
		a->width = 0;
	if (a->width >= a->precision && a->precision > countlen(x))
		a->width -= a->precision;
	else
		a->width -= (ft_strlen(s));
	(((size_t)a->precision > ft_strlen(s)) && (a->precision != -1))
	? (a->precision -= ft_strlen(s)) : (a->precision = 0);
	while (!a->flag[0] && a->width-- > 0 && ++(*count))
		ft_putchar(' ');
	((a->flag[3]) && (x > 0) && (*count += 2)) ? (ft_putstr("0X")) : 0;
	while (a->flag[0] && a->width-- > 0 && ++(*count))
		ft_putchar(' ');
	while (a->precision-- > 0 && ++(*count))
		ft_putchar('0');
	x = 0;
	while (s[x] && ++(*count))
		ft_putchar(s[x++]);
}

void		to_hex_big_minus(t_spec *a, va_list v_lst, int *count)
{
	intmax_t	x;
	char 		*s;

	x = get_hex(a->length, v_lst);
	(a->flag[3]) ? a->width -= 2 : 0;
	if (a->width < a->precision)
		a->width = 0;
	(x == 0 && a->precision == 0)
	? (s = "") : (s = ft_itoa_base(x, w_base(a)));
	if (a->width >= a->precision && a->precision > countlen(x))
		a->width -= a->precision;
	else
		a->width -= (ft_strlen(s));
	((a->flag[3]) && (x > 0) && (*count += 2)) ? (ft_putstr("0X")) : 0;
	(((size_t)a->precision > ft_strlen(s)) && (a->precision != -1))
	? (a->precision -= ft_strlen(s)) : (a->precision = 0);
	x = 0;
	while (a->precision-- > 0 && ++(*count))
		ft_putchar('0');
	while (s[x] && ++(*count))
		ft_putchar(s[x++]);
	while (a->width-- > 0 && ++(*count))
		ft_putchar(' ');
}

void			to_octal(t_spec *a, va_list v_lst, int *count)
{
	uintmax_t	o;
	char 		*s;

	o = get_octal(a->length, v_lst);
	(o == 0 && a->precision == 0)
	? (s = "") : (s = ft_itoa_base_u(o, w_base(a)));
	(a->flag[3]) ? a->width-- : 0;
	if (a->width < a->precision)
		a->width = 0;
	if (a->width >= a->precision && a->precision > countlen(o))
		a->width -= a->precision;
	else
		a->width -= (ft_strlen(s));
	(((size_t)a->precision > ft_strlen(s)) && (a->precision != -1))
	? (a->precision -= ft_strlen(s)) : (a->precision = 0);
	while (a->width-- > 0 && ++(*count))
		ft_putchar(' ');
	while (a->precision-- > 0 && ++(*count))
		ft_putchar('0');
	o = 0;
	(a->flag[3] && ++(*count)) ? ft_putchar('0') : 0;
 	while (s[o] && ++(*count))
		ft_putchar(s[o++]);
}

void			to_octal_minus(t_spec *a, va_list v_lst, int *count)
{
	uintmax_t	o;
	char 		*s;

	o = get_octal(a->length, v_lst);
	if (a->width < a->precision)
		a->width = 0;
	(o == 0 && a->precision == 0)
	? (s = "") : (s = ft_itoa_base_u(o, w_base(a)));
	(a->flag[3]) ? a->width-- : 0;
	if (a->width >= a->precision && a->precision > countlen(o))
		a->width -= a->precision;
	else
		a->width -= (ft_strlen(s));
	(((size_t)a->precision > ft_strlen(s)) && (a->precision != -1))
	? (a->precision -= ft_strlen(s)) : (a->precision = 0);
	o = 0;
	while (a->precision-- > 0 && ++(*count))
		ft_putchar('0');
	(a->flag[3]) && ++(*count) ? ft_putchar('0') : 0;
	while (s[o] && ++(*count))
		ft_putchar(s[o++]);
	while (a->width-- > 0 && ++(*count))
		ft_putchar(' ');
}

void		to_pointer(t_spec *a, va_list v_lst, int *count)
{
	intmax_t	p;
	char 		*s;

	p = get_hex(a->length, v_lst);
	(p == 0 && a->precision == 0)
	? (s = "") : (s = ft_itoa_base_u(p, w_base(a)));
	if (a->width < a->precision)
		a->width = 0;
	if (a->width >= a->precision && a->precision > countlen(p))
		a->width -= a->precision;
	else
		a->width -= (ft_strlen(s));
	(((size_t)a->precision > ft_strlen(s)) && (a->precision != -1))
	? (a->precision -= ft_strlen(s)) : (a->precision = 0);
	(*count) += 2;
	a->width -= 2;
	while (!a->flag[0] && a->width-- > 0 && ++(*count))
		ft_putchar(' ');
	while (a->flag[0] && a->width-- > 0 && ++(*count))
		ft_putchar('0');
	ft_putstr("0x");
	while (a->precision-- > 0 && ++(*count))
		ft_putchar('0');
	p = 0;
	while (s[p] && ++(*count))
		ft_putchar((char)ft_tolower((s[p++])));
}

void			to_pointer_minus(t_spec *a, va_list v_lst, int *count)
{
	intmax_t	x;
	char 		*s;

	x = get_hex(a->length, v_lst);
	if (a->width < a->precision)
		a->width = 0;
	(x == 0 && a->precision == 0)
	? (s = "") : (s = ft_itoa_base_u(x, w_base(a)));
	if (a->width >= a->precision && a->precision > countlen(x))
		a->width -= a->precision;
	else
		a->width -= (ft_strlen(s));
	(((size_t)a->precision > ft_strlen(s)) && (a->precision != -1))
	? (a->precision -= ft_strlen(s)) : (a->precision = 0);
	x = 0;
	ft_putstr("0x");
	while (a->precision-- > 0 && ++(*count))
		ft_putchar('0');
	(*count) += 2;
	a->width -= 2;
	while (s[x] && ++(*count))
		ft_putchar((char)ft_tolower(s[x++]));
	while (a->width-- > 0 && ++(*count))
		ft_putchar(' ');
}

void			for_print(t_spec *spc, va_list v_lst, int *count)
{
	if (spc->type == 'd' || spc->type == 'D' || spc->type == 'i')
	{
		spc->flag[1]
		? to_int_minus(spc, v_lst, count)
		: to_int(spc, v_lst, count);
	}
	else if (spc->type == 's' || spc->type == 'S')
	{
		spc->flag[1]
		? (to_string_minus(spc, v_lst, count))
		: (to_string(spc, v_lst, count));
	}
	else if (spc->type == 'p')
	{
		spc->flag[1]
		? to_pointer_minus(spc, v_lst, count)
		: to_pointer(spc, v_lst, count);
	}
	else if (spc->type == 'o')
	{
		spc->flag[1]
		? to_octal_minus(spc, v_lst, count)
		: to_octal(spc, v_lst, count);

	}
	else if (spc->type == 'u' || spc->type == 'U')
	{
		!spc->flag[1]
		? to_uint(spc, v_lst, count)
		: to_uint_minus(spc, v_lst, count);
	}
	else if (spc->type == 'x')
	{
		spc->flag[1]
		? to_hex_minus(spc, v_lst, count)
		: to_hex(spc, v_lst, count);
	}
	else if (spc->type == 'X')
	{
		spc->flag[1]
		? to_hex_big_minus(spc, v_lst, count)
		: to_hex_big(spc, v_lst, count);
	}
	else if (spc->type == 'c' || spc->type == 'C')
		to_char(spc, v_lst, count);
}

int				foobar(const char *str, va_list v_lst, int *count)
{
	int		i;
	t_var	*tmp;
	t_spec 	*spec;

	i = 1;
	tmp_struct_init(&tmp);
	struct_init(&spec);
	while (str[i] && ((tmp->flag = if_flag(str[i])) ||
			(tmp->width = if_width(str + i)) ||
			(tmp->length = if_length(str + i)) ||
			(tmp->precision = if_precision(str + i))))
	{
		if (tmp->flag == 1)
			i += find_flag(str + i, spec);
		else if (tmp->width == 1)
			i += find_width(str + i, spec);
		else if (tmp->length == 1)
			i += find_length(str + i, spec);
		else if (tmp->precision == 1)
			i += find_precision(str + i, spec);
	}
	spec->type = str[i++];
	for_print(spec, v_lst, count);
	free(spec);
	free(tmp);
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
			i += foobar(str + i, ag, &count);
		else
		{
			ft_putchar(str[i++]);
			count++;
		}
	}
	va_end(ag);
	return (count);
}