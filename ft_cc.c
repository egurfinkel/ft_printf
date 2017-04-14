/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egurfink <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 21:56:01 by egurfink          #+#    #+#             */
/*   Updated: 2017/04/13 21:56:03 by egurfink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			else_char(int *count, char *ch)
{
	write(1, ch, 1);
	(*count)++;
}

void			to_char(t_spc *a, va_list v_lst, int *count, int flag)
{
	char		ch;
	char		symb;

	flag ? ch = get_char(v_lst)
	: (ch = a->type);
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

void			to_char_big(t_spc *a, va_list v_lst, int *count, int flag)
{
	to_char(a, v_lst, count, flag);
}

char			get_char(va_list v_lst)
{
	return ((char)va_arg(v_lst, int));
}

char			set_symb(const t_spc *a)
{
	char			symb;

	if (a->f[0])
		symb = '0';
	else
		symb = ' ';
	return (symb);
}
