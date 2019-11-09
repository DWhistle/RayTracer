/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreduce.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:50:04 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/06/27 16:45:06 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstreduce(t_list *lst, void *param, void *(*f)(t_list *l, void *p))
{
	if (lst && f)
	{
		while (lst)
		{
			param = f(lst, param);
			lst = lst->next;
		}
	}
	return (param);
}
