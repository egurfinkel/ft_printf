/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egurfink <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 15:02:20 by egurfink          #+#    #+#             */
/*   Updated: 2016/12/29 15:39:52 by egurfink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_strequ(char const *s1, char const *s2)
{
	size_t		i;

	i = 0;
	if ((!s1) || (!s2))
		return (0);
	while ((s1[i] != '\0') && (s2[i] != '\0') && (s1[i] == s2[i]))
		i++;
	if ((s1[i] == '\0' && s2[i] == '\0'))
		return (1);
	return (0);
}