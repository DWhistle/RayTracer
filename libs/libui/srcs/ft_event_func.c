/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 19:48:34 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/06/09 19:05:51 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_events.h"
#include "ft_window.h"
#include "SDL2/SDL.h"

static int		set_window_event(t_window *wnd, t_event_type eventtype,
			t_windowevent_func func, void *param)
{
	if (eventtype == FT_EVENT_DEFAULT)
		wnd->windowfunc = func;
	else if (eventtype == FT_EVENT_WINDOWFUNC)
		wnd->windowfunc = func;
	else if (eventtype == FT_EVENT_BEFORECLOSE)
		wnd->beforeclose = func;
	wnd->window_param = param;
	return (0);
}

static int		set_render_event(t_window *wnd, t_event_type eventtype,
			t_windowevent_func func, void *param)
{
	if (eventtype == FT_EVENT_RENDER)
		wnd->renderfunc = func;
	else if (eventtype == FT_EVENT_TICKFUNC)
		wnd->tickfunc = func;
	wnd->render_param = param;
	return (0);
}

static int		set_input_event(t_window *wnd, t_event_type eventtype,
			t_windowevent_func func, void *param)
{
	if (eventtype == FT_EVENT_KEYPRESS)
		wnd->keypress = func;
	else if (eventtype == FT_EVENT_MOUSEDOWN)
		wnd->mousedown = func;
	else if (eventtype == FT_EVENT_MOUSEMOVE)
		wnd->mousemove = func;
	else if (eventtype == FT_EVENT_MOUSEUP)
		wnd->mouseup = func;
	wnd->input_param = param;
	return (0);
}

int				set_event_function(void *wnd, t_event_type eventtype,
					t_windowevent_func func, void *param)
{
	t_window	*w;

	w = (t_window*)wnd;
	if (!wnd || !func)
		return (-1);
	if (eventtype == FT_EVENT_DEFAULT || eventtype == FT_EVENT_WINDOWFUNC
		|| eventtype == FT_EVENT_BEFORECLOSE)
		set_window_event(w, eventtype, func, param);
	else if (eventtype == FT_EVENT_RENDER || eventtype == FT_EVENT_TICKFUNC)
		set_render_event(w, eventtype, func, param);
	else if (eventtype == FT_EVENT_KEYPRESS || eventtype == FT_EVENT_MOUSEDOWN
		|| eventtype == FT_EVENT_MOUSEMOVE || eventtype == FT_EVENT_MOUSEUP)
		set_input_event(w, eventtype, func, param);
	return (0);
}
