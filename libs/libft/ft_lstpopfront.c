/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpopfront.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 23:55:29 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/04/04 04:22:07 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstpopfront(t_list **lst)
{
	t_list	*elem;

	elem = *lst;
	if (elem)
		*lst = (*lst)->next;
	return (elem);
}
