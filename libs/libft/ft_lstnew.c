/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 23:31:23 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/05/24 21:27:39 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_del(void *content, size_t size)
{
	ft_bzero(content, size);
	free(content);
}

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_elem;

	new_elem = (t_list*)malloc(sizeof(t_list));
	if (!new_elem)
		return (NULL);
	if (content == NULL)
	{
		new_elem->content = NULL;
		new_elem->content_size = 0;
	}
	else
	{
		new_elem->content_size = content_size;
		new_elem->content = malloc(content_size);
		if (!(new_elem->content))
		{
			ft_lstdel(&new_elem, &ft_del);
			new_elem = NULL;
			return (NULL);
		}
		new_elem->content = ft_memcpy(new_elem->content, content, content_size);
	}
	new_elem->next = NULL;
	return (new_elem);
}
