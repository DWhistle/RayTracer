/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_obj_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:45:18 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/02 11:46:48 by kmeera-r         ###   ########.fr       */
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

double	len_sphere(t_vec point, t_vec param)
{
	return (vec_len(point) - fabs(param.arr[0]));
}

double	len_cone(t_vec point, t_vec param)
{
	double q;

	q = vec_len(new_vec2(point.arr[0], point.arr[1]));
	return (fmin(vec_dotvec(param, new_vec2(q, point.arr[2])),
			vec_dotvec(new_vec2(param.arr[0],
			-param.arr[1]), new_vec2(q, point.arr[2]))));
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
	return (fabs(vec_dotvec(point, norm) + param.arr[3]));
}
