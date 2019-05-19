/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 23:50:09 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/03/16 03:38:23 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*temp;

	temp = (*alst)->next;
	while (temp)
	{
		ft_lstdelone(alst, del);
		*alst = temp;
		temp = (*alst)->next;
	}
	ft_lstdelone(alst, del);
	*alst = NULL;
}
