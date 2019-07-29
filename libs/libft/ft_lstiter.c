/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 12:55:15 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/29 21:52:57 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		f(temp);
		temp = temp->next;
	}
}

void	ft_lstiterp(t_list *lst, void *p, void (*f)(t_list*, void*))
{
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		f(temp, p);
		temp = temp->next;
	}
}
