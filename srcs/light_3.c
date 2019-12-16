/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:01:37 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/15 11:11:06 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

t_vec			get_disruption_obj(t_point_data shadow)
{
	t_vec point;
	t_vec disruption_vec;

	point = rot(shadow.obj->rot_quat, vec_sub(shadow.point, shadow.obj->point));
	if (shadow.obj->disruption.texture)
	{
		if (shadow.obj->type == SPHERE)
			disruption_vec = (get_pixel(get_uv_spehere(point), shadow.obj->disruption));
		else if (shadow.obj->type == CYLINDER)
			disruption_vec = (get_pixel(get_uv_cylinder(shadow.obj->disruption, point,
					shadow.obj->param.arr[2]), shadow.obj->disruption));
		else if (shadow.obj->type == CONE)
			disruption_vec = (get_pixel(get_uv_cone(shadow.obj->disruption, point),\
					shadow.obj->disruption));
		else if (shadow.obj->type == PLANE)
			disruption_vec = (get_pixel(get_uv_plane(shadow.obj->disruption, point),\
					shadow.obj->disruption));
		else
			return (shadow.obj->color);
		return (vec_dotdec(shadow.obj->color, disruption_vec.arr[0] / 256));
	}
	return (shadow.obj->color);
}

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
	return (get_disruption_obj(shadow));
}

t_point_data	get_point(t_scene *objs, t_vec vec,
							t_accuracy accuracy)
{
	t_point_data point_data;

	accuracy.delta = 0;
	point_data = ray_render(objs, vec, objs->cam, raymarching);
	return (point_data);
}

int				get_shadow(t_scene *objs, t_vec vec,\
							t_accuracy accuracy, t_point_data point_data)
{
	t_vec			point;
	t_point_data	shadow;

	point = point_data.point;
	objs->ignore = point_data.obj;
	shadow = raymarching(objs, vec, accuracy, point);
	objs->tr_intensity = 1;
	while (shadow.obj && shadow.obj->transparency)
	{
		objs->tr_intensity *= shadow.obj->transparency;
		objs->ignore = shadow.obj;
		accuracy.max_dist -= vec_len(vec_sub(shadow.point, point));
		point = shadow.point;
		shadow = raymarching(objs, vec, accuracy, point);
	}
	objs->ignore = 0;
	if (shadow.obj)
		return (1);
	return (0);
}
