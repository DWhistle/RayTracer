/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_sum.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:23:25 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/02 12:26:05 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec4	vec_sum(t_vec4 v1, t_vec4 v2)
{
	t_vec4	ret;

	ret.vec.x = v1.vec.x + v2.vec.x;
	ret.vec.y = v1.vec.y + v2.vec.y;
	ret.vec.z = v1.vec.z + v2.vec.z;
	ret.vec.w = v1.vec.w + v2.vec.w;
	return (ret);
}

t_vec4	vec_add(t_vec4 v1, ft_decimal val)
{
	t_vec4	ret;

	ret.vec.x = v1.vec.x + val;
	ret.vec.y = v1.vec.y + val;
	ret.vec.z = v1.vec.z + val;
	ret.vec.w = v1.vec.w + val;
	return (ret);
}

t_vec4	vec_sub(t_vec4 v1, t_vec4 v2)
{
	t_vec4	ret;

	ret.vec.x = v1.vec.x - v2.vec.x;
	ret.vec.y = v1.vec.y - v2.vec.y;
	ret.vec.z = v1.vec.z - v2.vec.z;
	ret.vec.w = v1.vec.w - v2.vec.w;
	return (ret);
}

int		vec_equ(t_vec4 v1, t_vec4 v2, ft_decimal eps)
{
	return (fabs(v1.vec.x - v2.vec.x) <= eps &&
			fabs(v1.vec.y - v2.vec.y) <= eps &&
			fabs(v1.vec.z - v2.vec.z) <= eps &&
			fabs(v1.vec.w - v2.vec.w) <= eps);
}

int		vec_ident(t_vec4 v1, t_vec4 v2)
{
	return (v1.vec.x == v2.vec.x &&
			v1.vec.y == v2.vec.y &&
			v1.vec.z == v2.vec.z &&
			v1.vec.w == v2.vec.w);
}
