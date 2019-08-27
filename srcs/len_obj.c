/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:26:59 by bturcott          #+#    #+#             */
/*   Updated: 2019/08/25 18:30:00 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __OPENCL_C_VERSION__
# include "ray_render.h"
#endif

double		len_triangular_prism(t_vec point, t_vec param)
{
	t_vec	q;

	q = vec_fabs(point);
	return (fmax(q.arr[2] - param.arr[1],\
			fmax(q.arr[0] * 0.866025 + point.arr[1] * 0.5,\
			-point.arr[1]) - param.arr[0] * 0.5));
}

double		len_capsule(t_vec point, t_vec param)
{
	point.arr[1] -= clamp1(point.arr[1], 0.0, param.arr[0]);
	return (vec_len(point) - param.arr[1]);
}

double		len_ellipsoid(t_vec point, t_vec param)
{
	double k0;
	double k1;

	k0 = vec_len(new_vec3(
		point.arr[0] / param.arr[0],
		point.arr[1] / param.arr[1],
		point.arr[2] / param.arr[2]));
	k1 = vec_len(new_vec3(
		point.arr[0] / param.arr[0] / param.arr[0],
		point.arr[1] / param.arr[1] / param.arr[1],
		point.arr[2] / param.arr[2] / param.arr[2]));
	return (k0 * (k0 - 1) / k1);
}

double		len_box(t_vec point, t_vec param)
{
	t_vec d;

	d = new_vec3(fabs(point.arr[0]), fabs(point.arr[1]), fabs(point.arr[2]));
	d = vec_sub(d, param);
	return (vec_len(vec_fmax(d, 0.0)) + fmin(fmax(d.arr[0],
	fmax(d.arr[1], d.arr[2])), 0));
}

ft_decimal	vec_len(t_vec4 vec)
{
	return (sqrt(vec_sqrdist(vec)));
}
