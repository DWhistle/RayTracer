/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_hexagonal_prism.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:53:20 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/05 14:55:02 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"

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
