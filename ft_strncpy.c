/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egurfink <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 14:59:14 by egurfink          #+#    #+#             */
/*   Updated: 2016/12/27 22:10:28 by egurfink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	size_t			i;

	i = 0;
	while (len != 0 && src[i])
	{
		dest[i] = src[i];
		i++;
		len--;
	}
	while (len != 0)
	{
		dest[i++] = '\0';
		len--;
	}
	return (dest);
}
