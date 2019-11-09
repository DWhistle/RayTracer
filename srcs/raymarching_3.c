/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:12:12 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/26 18:58:40 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

t_vec			get_normal(t_vec point, t_obj obj)
{
	double	e;
	t_vec	vec;

	e = 0.53;
	if (obj.normal_map.texture)
	{
		vec = vec_norm(normal_map(point, obj));
		vec = vec_dotdec(vec, -1);
		return (vec);
	}
	vec.arr[0] = (update_r(obj, vec_sum(point, new_vec3(e, 0, 0))) -\
					update_r(obj, vec_sub(point, new_vec3(e, 0, 0))));
	vec.arr[1] = (update_r(obj, vec_sum(point, new_vec3(0, e, 0))) -\
					update_r(obj, vec_sub(point, new_vec3(0, e, 0))));
	vec.arr[2] = (update_r(obj, vec_sum(point, new_vec3(0, 0, e))) -\
					update_r(obj, vec_sub(point, new_vec3(0, 0, e))));
	vec.arr[3] = 0;
	if (obj.neg)
		vec = vec_dotdec(vec, -1);
	return (vec_norm(vec));
}

double			update_r(t_obj new_obj, t_vec point)
{
	double len;

	point = vec_sub(point, new_obj.point);
	point = rot(new_obj.rot_quat, point);
	if (new_obj.fract > 0)
	{
		point.arr[0] = fmod(point.arr[0], new_obj.fract) - new_obj.fract * 0.5;
		point.arr[1] = fmod(point.arr[1], new_obj.fract) - new_obj.fract * 0.5;
		point.arr[2] = fmod(point.arr[2], new_obj.fract) - new_obj.fract * 0.5;
	}
	len = new_obj.len(point, new_obj.param);
	len = update_restriction(len, new_obj, point);
	len = displace(point, len, new_obj);
	return (len - new_obj.rad);
}

t_vec			normal_map(t_vec point, t_obj obj)
{
	point = rot(obj.rot_quat, vec_sub(point, obj.point));
	if (obj.normal_map.texture)
	{
		if (obj.type == SPHERE)
			return (get_pixel(get_uv_spehere(point), obj.normal_map));
		else if (obj.type == CYLINDER)
			return (get_pixel(get_uv_cylinder(obj.normal_map, point,\
					obj.param.arr[2]), obj.normal_map));
		else if (obj.type == CONE)
			return (get_pixel(get_uv_cone(obj.normal_map, point),\
					obj.normal_map));
		else if (obj.type == PLANE)
			return (get_pixel(get_uv_plane(obj.normal_map, point),\
					obj.normal_map));
	}
	return (new_vec0());
}
