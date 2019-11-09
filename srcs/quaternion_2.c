/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:10:06 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/26 18:58:40 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quat.h"

t_quat	create_quat(t_vec4 rotate_vector, double rotate_angle)
{
	t_quat quat;

	rotate_vector = vec_norm(rotate_vector);
	quat.w = cos(rotate_angle / 2);
	quat.x = rotate_vector.arr[0] * sin(rotate_angle / 2);
	quat.y = rotate_vector.arr[1] * sin(rotate_angle / 2);
	quat.z = rotate_vector.arr[2] * sin(rotate_angle / 2);
	return (quat);
}

t_quat	quat_mul_quat(t_quat a, t_quat b)
{
	t_quat res;

	res.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
	res.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
	res.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
	res.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
	return (res);
}

t_quat	quat_mul_vector(t_quat a, t_vec4 b)
{
	t_quat res;

	res.w = -a.x * b.arr[0] - a.y * b.arr[1] - a.z * b.arr[2];
	res.x = a.w * b.arr[0] + a.y * b.arr[2] - a.z * b.arr[1];
	res.y = a.w * b.arr[1] - a.x * b.arr[2] + a.z * b.arr[0];
	res.z = a.w * b.arr[2] + a.x * b.arr[1] - a.y * b.arr[0];
	return (res);
}

double	quat_length(t_quat q)
{
	return (sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z));
}

t_quat	quat_scale(t_quat q, double val)
{
	q.w = q.w * val;
	q.x = q.x * val;
	q.y = q.y * val;
	q.z = q.z * val;
	return (q);
}
