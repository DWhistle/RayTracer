/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_window_params.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 00:17:29 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/29 21:52:57 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_window.h"

void		ft_set_window_color(void *wnd, unsigned int color)
{
	t_window	*w;

	w = (t_window*)wnd;
	w->color = color;
}

void		ft_set_window_position(void *wnd, int x, int y)
{
	t_window	*w;

	w = (t_window*)wnd;
	w->pos_x = x;
	w->pos_y = y;
}

void		ft_set_window_size(void *wnd, int w, int h)
{
	t_window	*ww;

	ww = (t_window*)wnd;
	ww->width = w;
	ww->height = h;
}

void		ft_set_window_title(void *wnd, char const *title)
{
	t_window	*w;

	w = (t_window*)wnd;
	w->title = title;
}

void		ft_set_window_quit(void *wnd, int quit)
{
	t_window	*w;

	w = (t_window*)wnd;
	w->quit = quit;
}
