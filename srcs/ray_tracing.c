/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:10:21 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/02 12:10:22 by kmeera-r         ###   ########.fr       */
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

void	ray_tracing(t_scene *scene, int **pixel,
					t_accuracy accuracy)
{
	int			x;
	int			y;
	t_vec		color;

	y = scene->h;
	while (y--)
	{
		x = scene->w;
		while (x--)
		{
			color = antialiasing(scene, (double)x / scene->w - 0.5,
			((double)y - scene->h / 2) / scene->w,\
			scene->points_data + x + scene->w * y);
			color = check_color(color);
			if (accuracy.depth_pt == 1)
				scene->color[x + scene->w * y] = color;
			else
				scene->color[x + scene->w * y] =\
				vec_sum(scene->color[x + scene->w * y], color);
			color = vec_dotdec(scene->color[x + scene->w * y],\
								1.0 / accuracy.depth_pt);
			(*pixel)[x + scene->w * y] = (int)(color.arr[0]) << 16 |
					(int)(color.arr[1]) << 8 | (int)(color.arr[2]) | 0xff << 24;
		}
	}
}
