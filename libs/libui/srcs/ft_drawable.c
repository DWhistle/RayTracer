/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 14:34:39 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/29 21:52:57 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftui.h>
#include "ft_control.h"
#include "ft_point.h"
#include "ft_window.h"

void	ft_draw_circle(void *pixels, t_rect *dst, t_rect *src, int color)
{
	int		i;
	int		j;
	int		n;

	i = -src->w / 2;
	while (i < src->w / 2)
	{
		j = -src->h / 2;
		while (j < src->h / 2)
		{
			if (i * i + j * j <= src->w * src->w / 4)
			{
				n = src->x + j + (src->y + i) * dst->w;
				if (n >= 0 && n <= dst->w * dst->h)
					((unsigned int*)pixels)[n] =
							ft_blend(color, ((unsigned int*)pixels)[n]);
			}
			++j;
		}
		++i;
	}
}

void	ft_draw_point(void *ctrl, t_point point, int color, int size)
{
	t_rect	r_point;
	t_rect	w_rect;
	int		*pxls;

	pxls = (int*)(((t_control*)ctrl)->pixels);
	if (!pxls)
		return ;
	w_rect = ft_get_control_rect(ctrl);
	r_point = ft_new_rect(point.x, point.y, size, size);
	ft_draw_circle(pxls, &w_rect, &r_point, color);
}

void	draw_line(void *ctrl, t_point *start_end, int color, int size)
{
	float	x;
	float	y;
	int		i;
	int		len;

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
		ft_draw_point(ctrl, ft_new_point((int)x, (int)y), color, size);
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
