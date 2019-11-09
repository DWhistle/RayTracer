/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:11:35 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/26 18:58:40 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

double			mix(double x, double y, double a)
{
	return (x * (1 - a) + y * a);
}

double			smooth_union(double d1, double d2, double k)
{
	double h;

	h = clamp1(0.5 + 0.5 * (d2 - d1) / k, 0.0, 1.0);
	return (mix(d2, d1, h) - k * h * (1.0 - h));
}

double			update_restriction(double r, t_obj obj, t_vec point)
{
	t_vec	norm;
	int		n;
	t_vec	new_point;

	if (!obj.restriction)
		return (r);
	n = obj.numbers_plane;
	while (n--)
	{
		norm = obj.restriction[n].norm;
		new_point = vec_sum(point, obj.restriction[n].dislocation);
		r = fmax(r, new_point.arr[0] * norm.arr[0] +\
						new_point.arr[1] * norm.arr[1] +\
						new_point.arr[2] * norm.arr[2]);
	}
	return (r);
}

double			displace(t_vec point, double r, t_obj obj)
{
	return (r + sin(obj.frequency * point.arr[0]) *\
			sin(obj.frequency * point.arr[2]) *\
			sin(obj.frequency * point.arr[1]) * obj.amplitude);
}

double			onion(double len, double h)
{
	return (fabs(len) - h);
}
