/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:05:10 by bturcott          #+#    #+#             */
/*   Updated: 2019/09/10 20:12:39 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"
#include "ftui.h"

t_vec	cartoon(t_vec color)
{
	int i;
	int a;

	i = 255;
	a = 50;
	while (i > 0)
	{
		if (color.arr[0] < i && color.arr[0] > i - a)
			color.arr[0] = i;
		if (color.arr[1] < i && color.arr[1] > i - a)
			color.arr[1] = i;
		if (color.arr[2] < i && color.arr[2] > i - a)
			color.arr[2] = i;
		i -= a;
	}
	return (color);
}

t_vec	negative(t_vec color)
{
	color.arr[0] = 255 - color.arr[0];
	color.arr[1] = 255 - color.arr[1];
	color.arr[2] = 255 - color.arr[2];
	return (color);
}

t_vec	sepia(t_vec color)
{
	color.arr[0] = (color.arr[0] + color.arr[1] + color.arr[2] + 112) / 4;
	color.arr[1] = (color.arr[0] + color.arr[1] + color.arr[2] + 66) / 4;
	color.arr[2] = (color.arr[0] + color.arr[1] + color.arr[2] + 20) / 4;
	return (color);
}

t_vec	stereoscopy(t_vec color, int i)
{
	color.arr[(i + 1) % 3] = 0;
	color.arr[(i + 2) % 3] = 0;
	return (color);
}

void	calculate_blur(int *color, int *cc, int *pixels, int w)
{
	if (cc[0] - cc[2] > 0 && cc[1] - cc[2] > 0)
	{
		color[0] = pixels[cc[0] + w * cc[1]] / (256 * 256)
			+ pixels[cc[0] - cc[2] + w * (cc[1] - cc[2])] / (256 * 256);
		color[1] = pixels[cc[0] + w * cc[1]] / 256 % 256
			+ pixels[cc[0] - cc[2] + w * (cc[1] - cc[2])] / 256 % 256;
		color[2] = pixels[cc[0] + w * cc[1]] % 256
			+ pixels[cc[0] - cc[2] + w * (cc[1] - cc[2])] % 256;
		pixels[cc[0] + w * cc[1]] = (color[0] / 2) * 256 * 256
			+ (color[1] / 2) * 256 + (color[2] / 2);
	}
}

int		*motion_blur(int *pixels, int w, int h)
{
	int color[3];
	int cc[3];

	cc[2] = 1;
	while (cc[2] < 50)
	{
		cc[0] = w;
		while (cc[0]--)
		{
			cc[1] = h;
			while (cc[1]--)
			{
				calculate_blur(color, cc, pixels, w);
			}
		}
		cc[1] += cc[2];
	}
	return (pixels);
}

void	define_color(t_vec color, t_scene scene,
int *coords, t_accuracy accuracy)
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
	if (accuracy.depth_pt == 1)
		scene.color[coords[0] + scene.w * coords[1]] = color;
	else
		scene.color[coords[0] + scene.w *
			coords[1]] = vec_sum(scene.color[coords[0]
					+ scene.w * coords[1]], color);
}

void	ray_tracing(t_scene scene, int **pixel,
		t_accuracy accuracy, t_rect *screen)
{
	int			x;
	int			y;
	t_vec		color;

	screen = 0;
	y = scene.h;
	while (y--)
	{
		x = scene.w;
		while (x--)
		{
			color = antialiasing(scene, (double)x / scene.w - 0.5,
					((double)y - scene.h / 2) / scene.w,
					accuracy, scene.points_data + x + scene.w * y);
			define_color(color, scene, (int[]){x, y}, accuracy);
			color = vec_dotdec(scene.color[x + scene.w * y],
					1.0 / accuracy.depth_pt);
			(*pixel)[x + scene.w * y] = (int)(color.arr[0]) << 16 |
				(int)(color.arr[1]) << 8 | (int)(color.arr[2]) | 0xff << 24;
		}
	}
}
