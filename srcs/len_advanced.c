/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_advanced.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:18:40 by bturcott          #+#    #+#             */
/*   Updated: 2019/08/25 18:21:30 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"

double	clamp1(double f, double s, double t)
{
	if (f < s)
		return (s);
	else if (f > t)
		return (t);
	else
		return (f);
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

double	len_octahedron(t_vec point, t_vec param)
{
	double	m;
	t_vec	q;
	double	k;

	point = vec_fabs(point);
	m = point.arr[0] + point.arr[1] + point.arr[2] - param.arr[0];
	if (3.0 * point.arr[0] < m)
		q = point;
	else if (3.0 * point.arr[1] < m)
		q = new_vec3(point.arr[1], point.arr[2], point.arr[0]);
	else if (3.0 * point.arr[2] < m)
		q = new_vec3(point.arr[2], point.arr[0], point.arr[1]);
	else
		return (m * 0.57735027);
	k = clamp1(0.5 * (q.arr[2] - q.arr[1] + param.arr[0]), 0.0, param.arr[0]);
	return (vec_len(new_vec3(q.arr[0],
	q.arr[1] - param.arr[0] + k, q.arr[2] - k)));
}
