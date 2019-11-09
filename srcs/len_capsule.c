/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_capsule.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:53:12 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/05 14:55:09 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"

double	len_capsule(t_vec point, t_vec param)
{
	point.arr[1] -= clamp1(point.arr[1], 0.0, param.arr[0]);
	return (vec_len(point) - param.arr[1]);
}
