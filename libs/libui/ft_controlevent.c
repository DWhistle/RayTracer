/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controlevent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 16:00:55 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/06/20 16:03:59 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui/ft_control.h"
#include "ftui.h"

int		set_controlevent_function(void *const ctrl, t_event_type eventtype,
				t_controlevent_func func, void *const param)
{
	t_control	*c;

	if (!ctrl || !func)
		return (-1);
	c = (t_control*)ctrl;
	if (eventtype == FT_EVENT_RENDER)
		c->ondraw = func;
	else if (eventtype == FT_EVENT_MOUSEDOWN)
		c->onmousedown = func;
	else if (eventtype == FT_EVENT_MOUSEMOVE)
		c->onmousemove = func;
	else if (eventtype == FT_EVENT_MOUSEUP)
		c->onmouseup = func;
	else if (eventtype == FT_EVENT_TICKFUNC)
		c->ontickfunc = func;
	c->param = param;
	return (0);
}
