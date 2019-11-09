/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:53:14 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/05 14:55:08 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"

double	len_cone(t_vec point, t_vec param)
{
	double q;

	q = vec_len(new_vec2(point.arr[0], point.arr[1]));
	return (fmin(vec_dotvec(param, new_vec2(q, point.arr[2])),
			vec_dotvec(new_vec2(param.arr[0],
			-param.arr[1]), new_vec2(q, point.arr[2]))));
}
