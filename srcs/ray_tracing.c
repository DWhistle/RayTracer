/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:10:21 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/26 18:58:40 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"
#include "ftui.h"
#include "effects.h"

t_vec	check_color(t_vec color)
{
	if (color.arr[0] > 255)
	{
		color.arr[1] += color.arr[0] - 255;
		color.arr[0] = 255;
	}
	if (color.arr[1] > 255)
	{
		color.arr[2] += color.arr[1] - 255;
		color.arr[1] = 255;
	}
	if (color.arr[2] > 255)
	{
		color.arr[0] += color.arr[2] - 255;
		color.arr[2] = 255;
	}
	if (color.arr[0] > 255)
		color.arr[0] = 255;
	return (color);
}

t_vec	get_effects(const t_scene *scene, t_vec *color)
{
	if (scene->sepia)
		(*color) = sepia((*color));
	if (scene->ce)
		(*color) = cartoon((*color));
	if (scene->neg)
		(*color) = negative((*color));
	if (scene->ster)
		(*color) = stereoscopy((*color), scene->ster);
	return (*color);
}

void	ray_tracing(t_scene *s, int **pixel, t_accuracy accuracy)
{
	int			x;
	int			y;
	t_vec		color;

	y = s->h;
	while (y--)
	{
		x = s->w;
		while (x--)
		{
			color = antialiasing(s, (double)x / s->w - 0.5,
	((double)y - s->h / 2) / s->w, s->points_data + x + s->w * y);
			color = check_color(color);
			if (accuracy.depth_pt == 1)
				s->color[x + s->w * y] = color;
			else
				s->color[x + s->w * y] = vec_sum(s->color[x + s->w * y], color);
			color = vec_dotdec(s->color[x + s->w * y], 1.0 / accuracy.depth_pt);
			color = get_effects(s, &color);
			(*pixel)[x + s->w * y] = (int)(color.arr[0]) << 16 |
				(int)(color.arr[1]) << 8 | (int)(color.arr[2]) | 0xff << 24;
		}
	}
	if (s->bm)
		*pixel = motion_blur(*pixel, s->w, s->h);
}
