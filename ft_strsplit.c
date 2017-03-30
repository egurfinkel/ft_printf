/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egurfink <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 17:30:40 by egurfink          #+#    #+#             */
/*   Updated: 2016/12/29 16:25:40 by egurfink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	words(char const *s, char c, size_t len)
{
	size_t		countwords;
	size_t		i;

	countwords = 0;
	i = 0;
	if (len == 0)
		return (0);
	while (i < len - 1)
	{
		while ((s[i] == c) && (i < len))
			i++;
		while ((s[i] != c) && (i < len))
			i++;
		countwords++;
	}
	return (countwords);
}

static size_t	lenchr(char const *s, char c, size_t i, size_t len)
{
	size_t		chr;

	chr = 0;
	while ((s[i] != c) && (i < len))
	{
		chr++;
		i++;
	}
	return (chr);
}

static void		charput(char const *s, char **out, char c, size_t len)
{
	size_t		n;
	size_t		str_m;
	size_t		i;
	size_t		lens;

	str_m = 0;
	i = 0;
	while (i < len)
	{
		while ((s[i] == c) && (i < len))
			i++;
		if (s[i] == '\0')
			break ;
		lens = lenchr(s, c, i, len);
		out[str_m] = (char*)malloc(lens + 1);
		n = 0;
		while (s[i] != c && s[i])
			out[str_m][n++] = s[i++];
		out[str_m][n] = '\0';
		str_m++;
	}
	out[str_m] = NULL;
}

char			**ft_strsplit(char const *s, char c)
{
	char		**out;
	size_t		len;

	len = 0;
	if (!s || !c)
		return (0);
	while (s[len])
		len++;
	if (!(out = (char**)malloc(sizeof(char*) * ((words(s, c, len)) + 1))))
		return (NULL);
	charput(s, out, c, len);
	return (out);
}
