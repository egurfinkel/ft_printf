/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egurfink <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 17:06:00 by egurfink          #+#    #+#             */
/*   Updated: 2017/03/25 16:16:15 by egurfink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

typedef struct 	s_spec
{
	int			precision;
	int			flag[5]; // '0' == 0, '-' == 1, '+' == 2, '#' == 3, ' ' == 4
	int			width;
	int			length; // 1 == 'hh', 2 == 'h', 3 == 'l', 4 == 'll', 5 == 'z', 6 == 'j'
	char		type;
	int 		h;
	int 		l;
}				t_spec;

typedef struct 	tmp_var
{
	int 		flag;
	int 		width;
	int 		precision;
	int 		length;
}				t_var;

int				ft_printf(const char *str, ...);
int				foobar(const char *str, va_list v_lst, int *count);
void			struct_init(t_spec **str);
void			tmp_struct_init(t_var **str);
int				countlen(intmax_t n);
int				if_width(const char *s);
int				if_length(const char *s);
int				if_precision(const char *s);
int				if_flag(const char ch);
int				find_flag(const char *s, t_spec *a);
int				find_width(const char *s, t_spec *a);
int				find_precision(const char *s, t_spec *a);
int				find_length(const char *s, t_spec *a);
void			to_hex(t_spec *a, va_list v_lst, int *count);
void			to_hex_minus(t_spec *a, va_list v_lst, int *count);
void			to_hex_big(t_spec *a, va_list v_lst, int *count);
void			to_hex_big_minus(t_spec *a, va_list v_lst, int *count);
void			to_char(t_spec *a, va_list v_lst, int *count, int flag);
void			to_int(t_spec *a, va_list v_lst, int *count);
void			to_int_minus(t_spec *a, va_list v_lst, int *count);
void			to_string(t_spec *a, va_list v_lst, int *count);
void			to_string_minus(t_spec *a, va_list v_lst, int *count);
void			to_pointer(t_spec *a, va_list v_lst, int *count);
void			to_pointer_minus(t_spec *a, va_list v_lst, int *count);
void			to_octal(t_spec *a, va_list v_lst, int *count);
void			to_uint(t_spec *a, va_list v_lst, int *count);
void			to_uint_minus(t_spec *a, va_list v_lst, int *count);
void			to_percent(t_spec *a, va_list v_lst, int *count);
void			for_print(t_spec *spc, va_list v_lst, int *count);
char			get_char(va_list v_lst);
intmax_t		get_int(int len, va_list v_lst);
uintmax_t 		get_uint(int len, va_list v_lst);
uintmax_t 		get_hex(int len, va_list v_lst);
uintmax_t		get_octal(int len, va_list v_lst);
void			f(intmax_t value, int base, char *str, int *i);
char			*ft_itoa_base(intmax_t value, int base);
void			uf(uintmax_t value, unsigned int base, char *str, int *i);
char			*ft_itoa_base_u(uintmax_t value, unsigned int base);
unsigned int	w_base(t_spec *a);
//void			free_struct(t_spec *spec, t_var *tmp);

#endif
