/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_box_fract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:53:04 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/05 15:00:31 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"

float		maxcomp(t_vec p)
{
	return (fmax(p.vec.x, fmax(p.vec.y, p.vec.z)));
}

float		sd_cross(t_vec point, t_vec param)
{
	double da;
	double db;
	double dc;

	param.arr[0] = 0;
	da = maxcomp(vec_fabs(new_vec2(point.arr[0], point.arr[1])));
	db = maxcomp(vec_fabs(new_vec2(point.arr[1], point.arr[2])));
	dc = maxcomp(vec_fabs(new_vec2(point.arr[2], point.arr[0])));
	return (fmin(da, fmin(db, dc)) - 1.0);
}

double		len_box_fract(t_vec point, t_vec param)
{
	double	d;
	t_vec	a;
	double	s;
	double	c;
	int		m;

	s = 1.0;
	a = new_vec0();
	d = len_box(point, param);
	point = vec_sub(point, new_vec3(-1, -1, -1));
	m = -1;
	while (m++ < 4)
	{
		a = vec_dotdec(point, s);
		a.arr[0] = (fmod(a.arr[0], 2.0) - 1.0) * 3;
		a.arr[1] = (fmod(a.arr[1], 2.0) - 1.0) * 3;
		a.arr[2] = (fmod(a.arr[2], 2.0) - 1.0) * 3;
		s *= 3.0;
		c = (sd_cross(a, param)) / s;
		d = fmax(d, -c);
	}
	return (d);
}
