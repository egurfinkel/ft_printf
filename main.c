/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egurfink <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 17:58:49 by egurfink          #+#    #+#             */
/*   Updated: 2017/03/25 18:02:44 by egurfink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"
#include <limits.h>

int			main()
{
	int		i1;
	int		i2;
	char 	*s;

	s = "kek";
	i1 = ft_printf("\nM:{%+#zlljhh050.50p}\n", LONG_LONG_MIN);
	   i2 = printf("\nO:{%+#zlljhh050.50p}\n", LONG_LONG_MIN);

	printf("\n[M:%d][O:%d]\n", i1, i2);
	return (0);
}
