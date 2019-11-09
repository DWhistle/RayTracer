/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_obj_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:49:31 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/26 18:58:40 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"

double	len_tor(t_vec point, t_vec param)
{
	t_vec q;

	q = new_vec2(vec_len(new_vec2(point.arr[0], point.arr[2]))\
				- param.arr[0], point.arr[1]);
	return (vec_len(q) - param.arr[1]);
}

double	len_hexagonal_prism(t_vec point, t_vec param)
{
	const t_vec	k = new_vec3(-0.8660254, 0.5, 0.57735);
	t_vec		vec;
	t_vec		d;

	point = vec_fabs(point);
	vec = vec_dotdec(new_vec2(k.arr[0], k.arr[1]),\
		2.0 * fmin(vec_dotvec(new_vec2(k.arr[0], k.arr[1]),\
		new_vec2(point.arr[0], point.arr[1])), 0));
	point = vec_sub(point, vec);
	d = new_vec2(vec_len(vec_sub(new_vec2(point.arr[0], point.arr[1]),\
		new_vec2(clamp1(point.arr[0], -k.arr[2] * param.arr[0],\
		k.arr[2] * param.arr[0]), param.arr[0])))\
		* point.arr[1] - param.arr[0] > 0 ? 1 : -1,\
		point.arr[2] - param.arr[1]);
	return (fmin(fmax(d.arr[0], d.arr[1]), 0) + vec_len(vec_fmax(d, 0)));
}

double	len_triangular_prism(t_vec point, t_vec param)
{
	t_vec	q;

	q = vec_fabs(point);
	return (fmax(q.arr[2] - param.arr[1],\
			fmax(q.arr[0] * 0.866025 + point.arr[1] * 0.5,\
			-point.arr[1]) - param.arr[0] * 0.5));
}

double	len_capsule(t_vec point, t_vec param)
{
	point.arr[1] -= clamp1(point.arr[1], 0.0, param.arr[0]);
	return (vec_len(point) - param.arr[1]);
}

double	len_ellipsoid(t_vec point, t_vec param)
{
	double k0;
	double k1;

	k0 = vec_len(new_vec3(point.arr[0] / param.arr[0],
							point.arr[1] / param.arr[1],
							point.arr[2] / param.arr[2]));
	k1 = vec_len(new_vec3(point.arr[0] / param.arr[0] / param.arr[0],
							point.arr[1] / param.arr[1] / param.arr[1],
							point.arr[2] / param.arr[2] / param.arr[2]));
	return (k0 * (k0 - 1) / k1);
}
