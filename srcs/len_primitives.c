/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_primitives.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 18:13:19 by bturcott          #+#    #+#             */
/*   Updated: 2019/08/25 18:17:53 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"

double	len_sphere(t_vec point, t_vec param)
{
	return (vec_len(point) - fabs(param.arr[0]));
}

double	len_cone(t_vec point, t_vec param)
{
	double q;

	q = vec_len(new_vec2(point.arr[0], point.arr[1]));
	return (fmin(vec_dotvec(param, new_vec2(q, point.arr[2])),
				vec_dotvec(new_vec2(param.arr[0], -param.arr[1]),
				new_vec2(q, point.arr[2]))));
}

double	len_cylinder(t_vec point, t_vec param)
{
	return (vec_len(vec_sub(new_vec2(point.arr[0], point.arr[2]),\
			new_vec2(param.arr[0], param.arr[1]))) - param.arr[2]);
}

double	len_plane(t_vec point, t_vec param)
{
	t_vec norm;

	norm = new_vec3(param.arr[0], param.arr[1], param.arr[2]);
	return (vec_dotvec(point, norm) + param.arr[3]);
}

double	len_tor(t_vec point, t_vec param)
{
	t_vec q;

	q = new_vec2(vec_len(new_vec2(point.arr[0], point.arr[2])) - param.arr[0],
	point.arr[1]);
	return (vec_len(q) - param.arr[1]);
}
