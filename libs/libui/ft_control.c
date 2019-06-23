/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 19:40:21 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/06/18 16:18:43 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui/ft_control.h"
#include "ftui.h"
#include "libft.h"

static	void		ft_set_window(t_list *children, void *wnd)
{
	if (children)
	{
		if (((t_control*)(children->content))->children)
			ft_lstiterp(((t_control*)(children->content))->children, wnd,
				ft_set_window);
		((t_control *)children->content)->parent = wnd;
	}
}

int					ft_attach_to_window(void *ctrl, void *wnd)
{
	t_list		*newlist;
	t_control	*c;
	t_window	*w;

	if (!ctrl || !wnd)
		return (ERR_POINTER);
	c = ctrl;
	w = wnd;
	c->parent = w;
	if (c->rect.w > 0 && c->rect.h > 0)
		c->pixels = ft_memalloc(sizeof(int) * c->rect.w * c->rect.h);
	else
		c->pixels = NULL;
	newlist = ft_memalloc(sizeof(t_control));
	newlist->content = ctrl;
	newlist->content_size = sizeof(t_control);
	newlist->next = NULL;
	ft_lstadd(&(w->controls), newlist);
	ft_lstiterp(c->children, w, ft_set_window);
	return (0);
}

int					ft_attach_to_control(void *ctrl, void *p)
{
	t_list		*newlist;
	t_control	*parent;
	t_control	*c;

	if (!ctrl || !p)
		return (ERR_POINTER);
	parent = p;
	c = ctrl;
	c->parent = parent->parent;
	if (c->rect.w > 0 && c->rect.h > 0)
		c->pixels = ft_memalloc(sizeof(int) * c->rect.w * c->rect.h);
	else
		c->pixels = NULL;
	newlist = ft_memalloc(sizeof(t_control));
	newlist->content = ctrl;
	newlist->content_size = sizeof(t_control);
	newlist->next = NULL;
	ft_lstadd(&parent->children, newlist);
	ft_lstiterp(c->children, parent->parent, ft_set_window);
	return (0);
}

void				*ft_create_new_control(t_rect r, unsigned int color)
{
	t_control	*cntrl;

	cntrl = ft_memalloc(sizeof(t_control));
	if (!cntrl)
		return (NULL);
	cntrl->rect.x = r.x;
	cntrl->rect.y = r.y;
	cntrl->rect.w = r.w;
	cntrl->rect.h = r.h;
	cntrl->bg_color = color;
	cntrl->surface = SDL_CreateRGBSurface(0, r.w, r.h,
			32, 0xff000000, 0xff0000, 0xff00, 0xff);
	cntrl->parent = NULL;
	cntrl->children = NULL;
	cntrl->onmouseup = NULL;
	cntrl->onmousedown = NULL;
	cntrl->onmousemove = NULL;
	cntrl->ondraw = NULL;
	cntrl->state = S_NONE;
	return (cntrl);
}

int					ft_dettach_from_control(void *find, void *p)
{
	t_list		*lst;
	t_list		*prev;
	t_control	*c;

	if (!p || !find)
		return (0);
	lst = ((t_control*)p)->children;
	prev = NULL;
	while (lst)
	{
		c = (t_control*)lst->content;
		if (c == find)
		{
			if (prev)
				prev->next = lst->next;
			ft_lstdelone(&lst, NULL);
			return (1);
		}
		else if (ft_dettach_from_control(find, c))
			return (2);
		prev = lst;
		lst = lst->next;
	}
	return (0);
}
