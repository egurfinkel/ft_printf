/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egurfink <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 17:06:00 by egurfink          #+#    #+#             */
/*   Updated: 2017/04/13 17:33:27 by egurfink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

/*
**  flag : |'0' -  0| |'-' -  1| |'+' -  2| |'#' -  3| |' ' -  4|
**length : |'hh' - 1| |'h' - 2|| |'l' - 3|| |'ll' - 4| |'z' - 5|| |'j' - 6|
*/

typedef struct		s_spec
{
	int				prc;
	int				f[5];
	int				wd;
	int				ln;
	char			type;
	int				h;
	int				l;
	int				wand;
}					t_spec;

typedef struct		s_temp
{
	int				f;
	int				w;
	int				p;
	int				l;
}					t_var;

int					countlen(intmax_t n);
unsigned int		w_base(t_spec *a);
int					if_width(const char *s);
int					if_length(const char *s);
int					if_precision(const char *s);
int					if_flag(const char ch);
void				struct_init(t_spec **str);
void				tmp_struct_init(t_var **str);
int					find_flag(const char *s, t_spec *a);
int					find_width(const char *s, t_spec *a);
int					find_precision(const char *s, t_spec *a);
void				find_lh(const char *s, t_spec *a);
int					find_length(const char *s, t_spec *a);
char				get_char(va_list v_lst);
char				*get_string(va_list v_lst);
intmax_t			get_int(int len, va_list v_lst);
uintmax_t			get_uint(int len, va_list v_lst);
uintmax_t			get_octal(int len, va_list v_lst);
uintmax_t			get_hex(int len, va_list v_lst);
char				set_symb(const t_spec *a);
void				else_char(int *count, char *ch);
void				to_char(t_spec *a, va_list v_lst, int *count, int flag);
void				to_char_big(t_spec *a, va_list v_lst, int *count, int flag);
void				string_magic(t_spec *a, int *count, const char *s, int i);
void				to_string(t_spec *a, va_list v_lst, int *count);
void				to_string_big(t_spec *a, va_list v_lst, int *count);
void				string_minus_magic\
						(t_spec *a, int *count, const char *s, int i);
void				to_string_minus(t_spec *a, va_list v_lst, int *count);
void				to_string_minus_big(t_spec *a, va_list v_lst, int *count);
void				int_magic(t_spec *a,\
		int *count, intmax_t i, const char *s);
void				to_int(t_spec *a, va_list v_lst, int *count);
void				int_minus_magic(t_spec *a, intmax_t i, const char *s);
void				to_int_minus(t_spec *a, va_list v_lst, int *count);
void				to_uint(t_spec *a, va_list v_lst, int *count);
void				to_uint_minus(t_spec *a, va_list v_lst, int *count);
void				to_hex(t_spec *a, va_list v_lst, int *count);
void				to_hex_minus(t_spec *a, va_list v_lst, int *count);
void				to_hex_big(t_spec *a, va_list v_lst, int *count);
void				to_hex_big_minus(t_spec *a, va_list v_lst, int *count);
void				to_octal(t_spec *a, va_list v_lst, int *count);
void				to_octal_minus(t_spec *a, va_list v_lst, int *count);
void				to_pointer(t_spec *a, va_list v_lst, int *count);
void				to_pointer_minus(t_spec *a, va_list v_lst, int *count);
void				to_percent(t_spec *a, va_list v_lst, int *count);
void				call_str(t_spec *spc, va_list v_lst, int *count);
void				call_int(t_spec *spc, va_list v_lst, int *count);
void				call_pointer(t_spec *spc, va_list v_lst, int *count);
void				call_octal(t_spec *spc, va_list v_lst, int *count);
void				call_uint(t_spec *spc, va_list v_lst, int *count);
void				call_hex(t_spec *spc, va_list v_lst, int *count);
void				call_char(t_spec *spc, va_list v_lst, int *count);
void				for_print(t_spec *spc, va_list v_lst, int *count);
void				init_struct(t_var **tmp, t_spec **spec);
void				free_struct(t_spec **spec, t_var **tmp);
int					ft_magic(const char *str, va_list v_lst, int *count);
int					ft_printf(const char *str, ...);
void				f(intmax_t value, int base, char *str, int *i);
char				*ft_itoa_base(intmax_t value, int base);
void				uf(uintmax_t value, unsigned int base, char *str, int *i);
char				*ft_itoa_base_u(uintmax_t value, unsigned int base);

#endif
