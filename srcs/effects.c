/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:23:07 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/09 15:49:04 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "effects.h"

t_vec4	cartoon(t_vec4 color)
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

t_vec4	negative(t_vec4 color)
{
	color.arr[0] = 255 - color.arr[0];
	color.arr[1] = 255 - color.arr[1];
	color.arr[2] = 255 - color.arr[2];
	return (color);
}

t_vec4	sepia(t_vec4 color)
{
	color.arr[0] = (color.arr[0] + color.arr[1] + color.arr[2] + 112) / 4;
	color.arr[1] = (color.arr[0] + color.arr[1] + color.arr[2] + 66) / 4;
	color.arr[2] = (color.arr[0] + color.arr[1] + color.arr[2] + 20) / 4;
	return (color);
}

t_vec4	stereoscopy(t_vec4 color, int i)
{
	color.arr[(i + 1) % 3] = 0;
	color.arr[(i + 2) % 3] = 0;
	return (color);
}

int		*motion_blur(int *pixels, int w, int h)
{
	t_motion_blur mb;

	mb.a = 1;
	while (mb.a < 25)
	{
		mb.x = w;
		while (mb.x--)
		{
			mb.y = h;
			while (mb.y--)
				if (mb.x - mb.a > 0 && mb.y - mb.a > 0)
				{
					mb.r = pixels[mb.x + w * mb.y] / (256 * 256)\
					+ pixels[mb.x - mb.a + w * (mb.y - mb.a)] / (256 * 256);
					mb.g = pixels[mb.x + w * mb.y] / 256 % 256\
					+ pixels[mb.x - mb.a + w * (mb.y - mb.a)] / 256 % 256;
					mb.b = pixels[mb.x + w * mb.y] % 256\
					+ pixels[mb.x - mb.a + w * (mb.y - mb.a)] % 256;
					pixels[mb.x + w * mb.y] = (mb.r / 2)\
					* 256 * 256 + (mb.g / 2) * 256 + (mb.b / 2);
				}
		}
		mb.a += mb.a;
	}
	return (pixels);
}
