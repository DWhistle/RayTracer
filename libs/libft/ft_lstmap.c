/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 12:55:38 by hgreenfe          #+#    #+#             */
/*   Updated: 2018/11/29 06:53:34 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

static void	ft_lstdelcontent(void *content, size_t size)
{
	ft_bzero(content, size);
	free(content);
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*temp;
	t_list	*newlst;
	t_list	*cur_lst;

	if (!lst || !f)
		return (NULL);
	cur_lst = lst;
	newlst = f(lst);
	if (!newlst)
		return (NULL);
	temp = newlst;
	while (cur_lst->next)
	{
		temp->next = f(cur_lst->next);
		if (!temp->next)
		{
			ft_lstdel(&newlst, &ft_lstdelcontent);
			return (NULL);
		}
		cur_lst = cur_lst->next;
		temp = temp->next;
	}
	return (newlst);
}
