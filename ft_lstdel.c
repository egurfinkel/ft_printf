/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egurfink <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 14:55:52 by egurfink          #+#    #+#             */
/*   Updated: 2016/12/29 14:56:00 by egurfink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*temp1;
	t_list	*temp2;

	temp1 = *alst;
	temp2 = NULL;
	while (temp1 != NULL)
	{
		del(temp1->content, temp1->content_size);
		temp2 = temp1->next;
		free(temp1);
		temp1 = temp2;
	}
	*alst = NULL;
}
