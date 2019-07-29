/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_window_params.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 15:06:15 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/29 21:52:57 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_window.h"

unsigned int	ft_get_window_color(void *wnd)
{
	t_window	*w;

	w = (t_window*)wnd;
	return (w->color);
}

t_point			ft_get_window_position(void *wnd)
{
	t_window	*w;
	t_point		pos;

	w = (t_window*)wnd;
	pos.x = w->pos_x;
	pos.y = w->pos_y;
	return (pos);
}

t_point			ft_get_window_size(void *wnd)
{
	t_window	*ww;
	t_point		size;

	ww = (t_window*)wnd;
	size.x = ww->width;
	size.y = ww->height;
	return (size);
}

char const		*ft_get_window_title(void *wnd)
{
	t_window	*w;

	w = (t_window*)wnd;
	return (w->title);
}

int				ft_get_window_quit(void *wnd)
{
	t_window	*w;

	w = (t_window*)wnd;
	return (w->quit);
}
