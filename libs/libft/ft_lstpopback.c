/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpopback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 23:55:29 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/04/04 04:21:57 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list				*ft_lstpopback(t_list **lst)
{
	t_list	*prev;
	t_list	*elem;

	elem = *lst;
	prev = NULL;
	if (!elem)
		return (NULL);
	while (elem->next)
	{
		prev = elem;
		elem = elem->next;
	}
	if (prev)
		prev->next = NULL;
	else
		return (NULL);
	return (elem);
}
