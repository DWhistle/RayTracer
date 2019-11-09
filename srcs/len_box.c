/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_box.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:53:07 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/05 14:53:08 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"

double		len_box(t_vec point, t_vec param)
{
	t_vec d;

	d = new_vec3(fabs(point.arr[0]), fabs(point.arr[1]), fabs(point.arr[2]));
	d = vec_sub(d, param);
	return (vec_len(vec_fmax(d, 0.0)) + fmin(fmax(d.arr[0],\
			fmax(d.arr[1], d.arr[2])), 0));
}
