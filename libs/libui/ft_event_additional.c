/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_additional.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 18:12:22 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/06/18 19:09:47 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftui.h"
#include "libft.h"
#include "libui/ft_window.h"
#include "libui/ft_events.h"

int		ft_intersect(t_control *control, t_point mouse)
{
	t_point	end;

	if (!control)
		return (0);
	end.x = control->rect.x + control->rect.w;
	end.y = control->rect.y + control->rect.h;
	if (control->rect.x <= mouse.x && control->rect.y <= mouse.y
		&& end.x >= mouse.x && end.y >= mouse.y)
		return (1);
	else
		return (0);
}

void	ft_set_event_pos(t_event *event, t_point pos)
{
	if (event->type == SDL_MOUSEBUTTONUP || event->type == SDL_MOUSEBUTTONDOWN)
	{
		event->button.x = pos.x;
		event->button.y = pos.y;
	}
	if (event->type == SDL_MOUSEMOTION)
	{
		event->motion.x = pos.x;
		event->motion.y = pos.y;
	}
}

void	ft_controllist_mouse_event(t_list *controls, void *event)
{
	t_control	*c;
	t_point		mouse;

	c = (t_control*)controls->content;
	mouse = ft_get_mouse_event_state(event, NULL);
	if (ft_intersect(c, mouse))
	{
		if (c->children)
		{
			mouse.x -= c->rect.x;
			mouse.y -= c->rect.y;
			ft_set_event_pos(event, mouse);
			ft_lstiterp(c->children, event, ft_controllist_mouse_event);
			mouse.x += c->rect.x;
			mouse.y += c->rect.y;
			ft_set_event_pos(event, mouse);
		}
		if (((t_event*)event)->type == SDL_MOUSEMOTION && c->onmousemove)
			c->onmousemove(c, ((t_event*)event)->motion.state, event);
		if (((t_event*)event)->type == SDL_MOUSEBUTTONUP && c->onmouseup)
			c->onmouseup(c, ((t_event*)event)->button.button, event);
		if (((t_event*)event)->type == SDL_MOUSEBUTTONDOWN && c->onmousedown)
			c->onmousedown(c, ((t_event*)event)->button.button, event);
	}
}

void	ft_window_mouse_event(t_window *wnd, t_event *event)
{
	if (wnd->controls)
		ft_lstiterp(wnd->controls, event, ft_controllist_mouse_event);
	if (event->type == SDL_MOUSEMOTION && wnd->mousemove)
		wnd->mousemove(wnd, event->motion.state, event);
	if (event->type == SDL_MOUSEBUTTONUP && wnd->mouseup)
		wnd->mouseup(wnd, event->button.button, event);
	if (event->type == SDL_MOUSEBUTTONDOWN && wnd->mousedown)
		wnd->mousedown(wnd, event->button.button, event);
}
