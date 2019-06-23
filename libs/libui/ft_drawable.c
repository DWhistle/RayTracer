/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 14:34:39 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/06/20 21:12:02 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftui.h"
#include "libui/ft_point.h"
#include "libui/ft_window.h"

t_point	ft_new_point(int x, int y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

t_rect	ft_new_rect(int x, int y, int w, int h)
{
	t_rect	r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return (r);
}

void	ft_draw_point(void *wnd, t_point point, int color, int size)
{
	int		i;
	int		j;
	int		n;
	int		*pxls;

	pxls = (int*)(((t_window*)wnd)->sdl_surface->pixels);
	i = -size / 2;
	while (i < size / 2)
	{
		j = -size / 2;
		while (j < size / 2)
		{
			if (i * i + j * j <= size * size * 0.25)
			{
				n = point.x + j + (point.y + i) *
								  ((t_window *) wnd)->sdl_surface->w;
				if (n >= 0
					&& n <= ((t_window *) wnd)->sdl_surface->h
							* ((t_window *) wnd)->sdl_surface->w)
					pxls[n] = color;
			}
			++j;
		}
		++i;
	}
}

void	draw_line(void *wnd, t_point *start_end, int color, int size)
{
	int		*pxls;
	float	x;
	float	y;
	int		i;
	int		len;

	pxls = (int*)(((t_window*)wnd)->sdl_surface->pixels);
	x = (float)(start_end[0].x);
	y = (float)(start_end[0].y);
	len = abs(start_end[1].x - start_end[0].x) > abs(start_end[1].y
			- start_end[0].y)
		? (start_end[1].x - start_end[0].x) : (start_end[1].y - start_end[0].y);
	i = 0;
	while (i < abs(len))
	{
		x += (float)(start_end[1].x - start_end[0].x) / fabsf((float)len);
		y += (float)(start_end[1].y - start_end[0].y) / fabsf((float)len);
		ft_draw_point(wnd, ft_new_point((int)x, (int)y), color, size);
		++i;
	}
}

void	ft_draw_rect(int *pxls, t_rect *rect, int width, int color)
{
	int		x;
	int		y;

	y = 0;
	while (y < rect->h)
	{
		x = 0;
		while (x < rect->w)
		{
			pxls[rect->x + x + (rect->y + y) * width] = color;
			++x;
		}
		++y;
	}
}
