/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_triangle_prism.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:53:59 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/05 14:54:32 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"

double	len_triangular_prism(t_vec point, t_vec param)
{
	t_vec	q;

	q = vec_fabs(point);
	return (fmax(q.arr[2] - param.arr[1],\
			fmax(q.arr[0] * 0.866025 + point.arr[1] * 0.5,\
			-point.arr[1]) - param.arr[0] * 0.5));
}
