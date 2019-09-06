/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparency.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:18:05 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/02 12:18:06 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"

t_vec	rot(t_quat quat, t_vec v)
{
	t_quat t;

	t = quat_mul_vector(quat, v);
	t = quat_mul_quat(t, quat_invert(quat));
	return (new_vec3(t.x, t.y, t.z));
}

t_vec	transparency(t_vec vec, t_point_data point)
{
	double	a;
	t_vec	v;

	a = acos(vec_dotvec(vec, point.norm));
	a = cos(asin(sin(a) * point.obj->refraction));
	v = rot(create_quat(vec_mul(vec, point.norm), a),\
			vec_dotdec(point.norm, -1));
	return (v);
}
