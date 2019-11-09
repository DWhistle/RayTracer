/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_ellipsoid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:53:18 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/05 14:55:04 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"

double	len_ellipsoid(t_vec point, t_vec param)
{
	double k0;
	double k1;

	k0 = vec_len(new_vec3(point.arr[0] / param.arr[0],
							point.arr[1] / param.arr[1],
							point.arr[2] / param.arr[2]));
	k1 = vec_len(new_vec3(point.arr[0] / param.arr[0] / param.arr[0],
							point.arr[1] / param.arr[1] / param.arr[1],
							point.arr[2] / param.arr[2] / param.arr[2]));
	return (k0 * (k0 - 1) / k1);
}
