/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_obj_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:49:41 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/02 11:50:32 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"

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
	return (vec_len(new_vec3(q.arr[0], q.arr[1]
			- param.arr[0] + k, q.arr[2] - k)));
}
