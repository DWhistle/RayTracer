/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:53:49 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/05 14:54:56 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"

double	len_plane(t_vec point, t_vec param)
{
	t_vec norm;

	norm = new_vec3(param.arr[0], param.arr[1], param.arr[2]);
	return (fabs(vec_dotvec(point, norm) + param.arr[3]));
}
