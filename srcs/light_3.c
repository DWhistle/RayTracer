/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:01:37 by kmeera-r          #+#    #+#             */
/*   Updated: 2020/01/13 19:20:59 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

t_vec			get_disruption_obj(t_point_data shadow)
{
	t_vec point;
	t_vec d_vec;

	point = rot(shadow.obj->rot_quat, vec_sub(shadow.point, shadow.obj->point));
	if (shadow.obj->disruption.texture)
	{
		if (shadow.obj->type == SPHERE)
			d_vec = (get_pixel(get_uv_spehere(point), shadow.obj->disruption));
		else if (shadow.obj->type == CYLINDER)
			d_vec = (get_pixel(get_uv_cylinder(shadow.obj->disruption, point,
					shadow.obj->param.arr[2]), shadow.obj->disruption));
		else if (shadow.obj->type == CONE)
			d_vec = (get_pixel(get_uv_cone(shadow.obj->disruption, point),\
					shadow.obj->disruption));
		else if (shadow.obj->type == PLANE)
			d_vec = (get_pixel(get_uv_plane(shadow.obj->disruption, point),\
					shadow.obj->disruption));
		else
			return (shadow.obj->color);
		return (vec_dotdec(shadow.obj->color, d_vec.arr[0] / 256));
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
		{
			point = rot(quat_from_vec(vec_mul(new_vec3(0, 0, 1),\
			shadow.norm)), point);
			return (get_pixel(get_uv_plane(shadow.obj->texture, point),\
					shadow.obj->texture));
		}
	}
	return (get_disruption_obj(shadow));
}

t_point_data	get_point(t_scene *objs, t_vec vec,
							t_accuracy accuracy)
{
	t_point_data point_data;

	accuracy.delta = 0;
	point_data = ray_render(objs, vec, objs->cam, 0);
	return (point_data);
}

int				get_shadow(t_scene *objs,\
							t_light_option *lo,\
							t_accuracy accuracy, t_point_data point_data)
{
	t_vec			point;
	t_point_data	shadow;

	point = vec_sum(point_data.point, lo->li);
	shadow = raymarching(objs, lo->li, accuracy, point);
	lo->tr_intensity = 1.0;
	while (shadow.obj && shadow.obj->transparency)
	{
		lo->tr_intensity *= shadow.obj->transparency;
		accuracy.max_dist -= vec_len(vec_sub(shadow.point, point));
		point = vec_sum(shadow.point, vec_dotdec(lo->li, accuracy.delta * 100));
		shadow = raymarching(objs, lo->li, accuracy, point);
	}
	if (shadow.obj)
		return (1);
	return (0);
}
