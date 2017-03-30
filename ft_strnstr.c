/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egurfink <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:49:48 by egurfink          #+#    #+#             */
/*   Updated: 2016/12/14 17:30:46 by egurfink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char		*ps1;
	char		*ps2;
	size_t		n;
	size_t		i;

	if (*little == '\0')
		return ((char*)big);
	ps1 = (char*)big;
	ps2 = (char*)little;
	n = ft_strlen(ps2);
	i = 0;
	while (ps1[i] != '\0' && (i + n) <= len)
	{
		if (ft_strncmp(big + i, little, n) == 0)
		{
			return (ps1 + i);
		}
		i++;
	}
	return (NULL);
}
