/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 23:55:29 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/05/24 21:27:39 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list				*ft_lstpushback(t_list *lst, t_list *new)
{
	t_list	*elem;

	elem = lst;
	if (!lst)
	{
		elem = new;
		return (new);
	}
	while (elem->next)
	{
		elem = elem->next;
	}
	elem->next = new;
	return (lst);
}
