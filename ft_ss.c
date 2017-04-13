/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ss.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egurfink <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 21:57:05 by egurfink          #+#    #+#             */
/*   Updated: 2017/04/13 21:57:07 by egurfink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			call_str(t_spc *spc, va_list v_lst, int *count)
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

void			to_string_big(t_spc *a, va_list v_lst, int *count)
{
	to_string(a, v_lst, count);
}

void			to_string_minus_big(t_spc *a, va_list v_lst, int *count)
{
	to_string_minus(a, v_lst, count);
}
