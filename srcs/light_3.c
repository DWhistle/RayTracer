/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:01:37 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/06 13:19:42 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

t_vec			get_uv_plane(t_texture texture, t_vec point)
{
	double v;
	double u;

	v = fmod(point.arr[0] / texture.len_v, 1);
	u = fmod(point.arr[1] / texture.len_u, 1);
	if (u < 0)
		u += 1;
	if (v < 0)
		v += 1;
	return (new_vec2(u, v));
}

t_vec			get_color_obj(t_point_data shadow)
{
	t_vec point;

	point = rot(shadow.obj->rot_quat, vec_sub(shadow.point, shadow.obj->point));
	if (shadow.obj->texture.texture)
	{
		if (shadow.obj->type == SPHERE)
			return (get_pixel(get_uv_spehere(point), shadow.obj->texture));
		else if (shadow.obj->type == CYLINDER)
			return (get_pixel(get_uv_cylinder(shadow.obj->texture, point,
					shadow.obj->param.arr[2]), shadow.obj->texture));
		else if (shadow.obj->type == CONE)
			return (get_pixel(get_uv_cone(shadow.obj->texture, point),\
					shadow.obj->texture));
		else if (shadow.obj->type == PLANE)
			return (get_pixel(get_uv_plane(shadow.obj->texture, point),\
					shadow.obj->texture));
	}
	return (shadow.obj->color);
}

t_point_data	get_point(t_scene *objs, t_vec vec,
							t_accuracy accuracy)
{
	t_point_data point_data;

	accuracy.delta = 0;
	point_data = ray_render(objs, vec, objs->cam, raymarching);
	return (point_data);
}
