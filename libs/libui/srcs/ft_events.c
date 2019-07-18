/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 13:08:48 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/06/18 18:53:51 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_events.h"
#include "ft_window.h"
#include "SDL2/SDL.h"

int		ft_events_main(void *w, t_event *event)
{
	t_window	*wnd;

	wnd = (t_window*)w;
	if (!wnd || !event || wnd->quit)
		return (1);
	if (event->type == SDL_QUIT)
		wnd->quit = 1;
	return (wnd->quit);
}

void	ft_keyboard_event(t_window *wnd, t_event *event)
{
	if (event->type == SDL_KEYDOWN)
		wnd->keys[event->key.keysym.scancode] = 1;
	else if (event->type == SDL_KEYUP)
	{
		wnd->keys[event->key.keysym.scancode] = 0;
		if (wnd->keypress)
			wnd->keypress(wnd, event->key.keysym.scancode, event);
	}
}

int		ft_input_main(void *w, t_event *event)
{
	t_window	*wnd;

	wnd = (t_window*)w;
	if (!wnd || !event || wnd->quit)
		return (1);
	if (event->type == SDL_QUIT)
		wnd->quit = 1;
	if (wnd->is_active)
	{
		if (event->type == SDL_KEYUP || event->type == SDL_KEYDOWN)
			ft_keyboard_event(w, event);
		if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONUP
									|| event->type == SDL_MOUSEBUTTONDOWN)
			ft_window_mouse_event(wnd, event);
	}
	return (wnd->quit);
}

int		ft_window_main(void *w, t_event *event)
{
	t_window	*wnd;

	wnd = (t_window*)w;
	if (!wnd || !event || wnd->quit)
		return (1);
	if (event->window.windowID == wnd->id)
	{
		if (wnd->windowfunc)
			wnd->windowfunc(wnd, event->window.event, event);
		if (event->window.event == SDL_WINDOWEVENT_CLOSE)
			wnd->quit = 1;
		if (event->window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
			wnd->is_active = 1;
		else if (event->window.event == SDL_WINDOWEVENT_FOCUS_LOST)
			wnd->is_active = 0;
	}
	return (wnd->quit);
}
