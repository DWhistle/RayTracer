/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:01:38 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/09 15:49:51 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

t_vec			rand_point(t_vec point, double r)
{
	t_vec	v;

	v = new_vec3(0, 0, 0);
	v.arr[0] = (rand() % 1024) * (rand() % 2 - 0.5);
	v.arr[1] = (rand() % 1024) * (rand() % 2 - 0.5);
	v.arr[2] = (rand() % 1024) * (rand() % 2 - 0.5);
	v = vec_norm(v);
	v = vec_dotdec(v, r);
	point = vec_sum(point, v);
	return (point);
}

t_vec			get_uv_spehere(t_vec point)
{
	double v;
	double u;
	double phi;
	double theta;

	point = vec_norm(point);
	phi = acos(-point.arr[2]);
	theta = acos(fmod(point.arr[1] / sin(phi), 1)) / (2.0 * 3.14);
	if (point.arr[0] > 0)
		u = theta;
	else
		u = (1 - theta);
	if (sin(phi) == 0)
		u = 1;
	v = (1.0 - phi / 3.14);
	return (new_vec2(u, v));
}

t_vec			get_pixel(t_vec uv, t_texture texture)
{
	double v;
	double u;

	u = (int)(uv.arr[0] * texture.h) * texture.w * 3;
	v = (int)(uv.arr[1] * texture.w) * 3;
	return (new_vec3(texture.texture[(int)v + (int)u + 2],
					texture.texture[(int)v + (int)u + 1],
					texture.texture[(int)v + (int)u]));
}

t_vec			get_uv_cylinder(t_texture texture, t_vec point, double param)
{
	double v;
	double u;

	point.arr[2] = point.arr[2] / param;
	point.arr[0] = point.arr[0] / param;
	v = cos(point.arr[2]);
	if (point.arr[0] < 0)
		v = fabs(v - 1);
	if (point.arr[2] < 0)
		v = fabs(v - 1);
	u = fmod(point.arr[1] / texture.len_u, 1);
	if (u < 0)
		u += 1;
	v *= 2;
	return (new_vec2(u, v));
}

t_vec			get_uv_cone(t_texture texture, t_vec point)
{
	double v;
	double u;
	double z;

	z = point.arr[2];
	point.arr[2] = 0;
	point = vec_norm(point);
	v = cos(point.arr[1]) * 2;
	u = fmod(fabs(z / texture.len_u), 1);
	return (new_vec2(u, v));
}
