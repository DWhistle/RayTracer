/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:10:01 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/26 18:58:40 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quat.h"
#include <stdio.h>

t_quat	quat_invert(t_quat q)
{
	t_quat res;

	res.w = q.w;
	res.x = -q.x;
	res.y = -q.y;
	res.z = -q.z;
	return (quat_scale(res, 1 / quat_length(res)));
}

t_quat	quat_from_vec(t_vec4 vec)
{
	t_quat	q;

	q.x = vec.vec.x;
	q.y = vec.vec.y;
	q.z = vec.vec.z;
	q.w = vec.vec.w;
	return (q);
}

t_vec4	vec_from_quat(t_quat q)
{
	t_vec4	vec;

	vec.vec.x = q.x;
	vec.vec.y = q.y;
	vec.vec.z = q.z;
	vec.vec.w = q.w;
	return (vec);
}
