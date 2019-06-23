/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 13:03:53 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/06/18 18:04:15 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftui.h"
#include "libui/ft_events.h"
#include "SDL2/SDL.h"

t_point			ft_get_mouse_pos(void)
{
	t_point		mouse;

	SDL_GetMouseState(&mouse.x, &mouse.y);
	return (mouse);
}

t_point			ft_get_mouse_event_state(void *event, int *state)
{
	t_point		mouse;
	t_event		*evnt;

	mouse.x = 0;
	mouse.y = 0;
	if (!event)
		return (mouse);
	evnt = (t_event*)event;
	if (evnt->type == SDL_MOUSEMOTION)
	{
		mouse.x = evnt->motion.x;
		mouse.y = evnt->motion.y;
		if (state)
			*state = evnt->motion.state;
	}
	else if (evnt->type == SDL_MOUSEBUTTONDOWN
			|| evnt->type == SDL_MOUSEBUTTONUP)
	{
		mouse.x = evnt->button.x;
		mouse.y = evnt->button.y;
		if (state)
			*state = evnt->button.state;
	}
	return (mouse);
}

char			ft_is_key_pressed(void *wnd, int keycode)
{
	t_window	*w;

	w = (t_window*)wnd;
	return (w->keys[keycode]);
}

int				ft_get_mouseevent(void *event_param)
{
	return ((int)event_param);
}
