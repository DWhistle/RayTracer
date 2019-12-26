/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 18:09:37 by bturcott          #+#    #+#             */
/*   Updated: 2019/12/26 14:46:00 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"
#include "ftui.h"
#include "effects.h"
#include <pthread.h>

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

void	effects1(t_scene *scene, t_vec *color, int **pixel, int pix)
{
	if (scene->sepia)
		*color = sepia(*color);
	if (scene->ster)
		*color = stereoscopy(*color, scene->ster);
	(*pixel)[pix] = (unsigned int)(color->arr[0]) << 16 |
		(unsigned int)(color->arr[1]) << 8 | (unsigned int)(color->arr[2])
		| 0xff << 24;
}

void	effects2(t_scene *scene, int **pixel)
{
	if (scene->bm)
		*pixel = motion_blur(*pixel, scene->w, scene->h);
}

t_vec	calc_color(t_pthread_param *param, int x, int y, int w)
{
	t_vec			color;

	color = antialiasing(param->scene, (double)x / w - 0.5,
			((double)y - param->scene->h * 0.5) / param->scene->h,
			param->scene->points_data + x + w * y);
	color = check_color(color);
	if (param->accuracy.depth_pt == 1)
		param->scene->color[x + w * y] = color;
	else
		param->scene->color[x + w * y] =\
										vec_sum(param->scene->color[x + w * y],
										color);
	color = vec_dotdec(param->scene->color[x + w * y],
				1.0 / param->accuracy.depth_pt);
	effects1(param->scene, &color, param->pixel, x + w * y);
	return (color);
}

void	*pthread_antialiasing(void *p_param)
{
	t_pthread_param	*param;
	int				y;
	int				x;
	int				w;
	t_vec			color;

	param = p_param;
	y = param->ymin - 1;
	w = param->scene->w;
	while (++y < param->ymax)
	{
		x = -1;
		while (++x < param->x)
		{
			color = calc_color(param, x, y, w);
		}
	}
	return (param);
}
