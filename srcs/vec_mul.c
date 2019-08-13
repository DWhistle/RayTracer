/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mul.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:40:37 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/29 21:52:57 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/vector.h"

double		vec_dotvec(t_vec4 v1, t_vec4 v2)
{
	return (v1.vec.x * v2.vec.x + v1.vec.y * v2.vec.y +\
			v1.vec.z * v2.vec.z + v1.vec.w * v2.vec.w);
}

t_vec4		vec_dotdec(t_vec4 v1, ft_decimal val)
{
	t_vec4	ret;

	ret.vec.x = v1.vec.x * val;
	ret.vec.y = v1.vec.y * val;
	ret.vec.z = v1.vec.z * val;
	ret.vec.w = v1.vec.w * val;
	return (ret);
}

t_vec4		vec_mul(t_vec4 v1, t_vec4 v2)
{
	t_vec4	ret;

	ret.vec.x = v1.vec.y * v2.vec.z - v1.vec.z * v2.vec.y;
	ret.vec.y = v1.vec.z * v2.vec.x - v1.vec.x * v2.vec.z;
	ret.vec.z = v1.vec.x * v2.vec.y - v1.vec.y * v2.vec.x;
	ret.vec.w = 1;
	return (ret);
}

ft_decimal	vec_sqrdist(t_vec4 vec)
{
	return (vec.vec.x * vec.vec.x +\
			vec.vec.y * vec.vec.y +\
			vec.vec.z * vec.vec.z +\
			vec.vec.w * vec.vec.w);
}

ft_decimal	vec_len(t_vec4 vec)
{
	return (sqrt(vec_sqrdist(vec)));
}

t_vec4		vec_norm(t_vec4 v)
{
	t_vec4		vec;
	ft_decimal	dist;

	dist = 1.0 / sqrt(vec_sqrdist(v));
	vec.vec.x = v.vec.x * dist;
	vec.vec.y = v.vec.y * dist;
	vec.vec.z = v.vec.z * dist;
	vec.vec.w = v.vec.w * dist;
	return (vec);
}
