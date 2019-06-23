/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control_destructors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 00:21:18 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/06/18 17:40:43 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui/ft_control.h"
#include "ftui.h"
#include "libft.h"

void					ft_clear_control(void *ctrl)
{
	t_control	*c;

	c = (t_control*)ctrl;
	if (c->pixels)
		ft_memdel(&(c->pixels));
	if (c->parent)
		c->parent = NULL;
	if (c->surface)
	{
		SDL_FreeSurface(c->surface);
		c->surface = NULL;
	}
	if (c->texture)
	{
		SDL_DestroyTexture(c->texture);
		c->texture = NULL;
	}
}

static void				ft_del_one_control(void *cntrl, size_t sz)
{
	t_control	*c;

	(void)sz;
	if (cntrl)
	{
		c = (t_control*)cntrl;
		if (c->children)
		{
			ft_delete_control(&(c->children->content));
		}
	}
}

void					ft_delete_control(void **cntrl)
{
	if (cntrl && *cntrl)
	{
		ft_clear_control(*cntrl);
		if (((t_control*)*cntrl)->children)
			ft_lstdel(&(((t_control*)*cntrl)->children), ft_del_one_control);
		ft_memset(*cntrl, 0, sizeof(t_control));
		ft_memdel((void **)cntrl);
	}
}

int						ft_dettach_from_window(void *ctrl, void *wnd)
{
	t_list		*lst;
	t_list		*prev;
	t_control	*c;

	if (!ctrl || !wnd)
		return (0);
	lst = ((t_window*)wnd)->controls;
	prev = NULL;
	while (lst)
	{
		c = (t_control*)lst->content;
		if (c == ctrl)
		{
			if (prev)
				prev->next = lst->next;
			ft_lstdelone(&lst, NULL);
			return (1);
		}
		prev = lst;
		lst = lst->next;
	}
	return (0);
}
