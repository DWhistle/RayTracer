/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:53:16 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/05 14:55:06 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"

double	len_cylinder(t_vec point, t_vec param)
{
	return (vec_len(vec_sub(new_vec2(point.arr[0], point.arr[2]),\
			new_vec2(param.arr[0], param.arr[1]))) - param.arr[2]);
}
