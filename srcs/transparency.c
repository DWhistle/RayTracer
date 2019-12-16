/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparency.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:18:05 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/12/16 09:25:09 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"

t_vec			rot(t_quat quat, t_vec v)
{
	t_quat t;

	t = quat_mul_vector(quat, v);
	t = quat_mul_quat(t, quat_invert(quat));
	return (new_vec3(t.x, t.y, t.z));
}

t_vec			transparency(t_vec vec, t_point_data point,
					double obj_refr, double refr)
{
	double	a;
	double	k;
	t_vec	v;

	obj_refr = refr / obj_refr;
	a = -vec_dotvec(vec, point.norm);
	k = 0;
	if (a < 0)
	{
		a *= -1;
		point.norm = vec_dotdec(point.norm, -1);
		obj_refr = 1.0 / obj_refr;
	}
	k = 1.0 - obj_refr * obj_refr * (1 - a * a);
	v = vec_norm(vec_sum(vec_dotdec(vec, obj_refr),\
	vec_dotdec(point.norm, a * obj_refr - sqrt(k))));
	return (v);
}

t_point_data	get_transparency(t_scene *objs,\
				t_vec vec, t_point_data point_data)
{
	t_point_data shadow;

	shadow = point_data;
	while (shadow.obj && shadow.obj->transparency)
	{
		objs->ignore = shadow.obj;
		shadow = ray_render(objs, vec, shadow.point, 0);
	}
	point_data.tranc_color = shadow.color;
	return (point_data);
}
