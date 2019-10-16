/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:24:39 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/09/26 18:58:40 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec4	new_vec(t_decimal val)
{
	t_vec4 vec;

	vec.vec.x = val;
	vec.vec.y = val;
	vec.vec.z = val;
	vec.vec.w = val;
	return (vec);
}

t_vec4	new_vec4(t_decimal valx, t_decimal valy, t_decimal valz,
					t_decimal valw)
{
	t_vec4 vec;

	vec.vec.x = valx;
	vec.vec.y = valy;
	vec.vec.z = valz;
	vec.vec.w = valw;
	return (vec);
}

t_vec4	new_vec3(t_decimal valx, t_decimal valy, t_decimal valz)
{
	t_vec4 vec;

	vec.vec.x = valx;
	vec.vec.y = valy;
	vec.vec.z = valz;
	vec.vec.w = 0.0;
	return (vec);
}

t_vec4	new_vec2(t_decimal valx, t_decimal valy)
{
	t_vec4 vec;

	vec.vec.x = valx;
	vec.vec.y = valy;
	vec.vec.z = 0.0;
	vec.vec.w = 0.0;
	return (vec);
}

t_vec4	new_vec0(void)
{
	t_vec4 vec;

	vec.vec.x = 0.0;
	vec.vec.y = 0.0;
	vec.vec.z = 0.0;
	vec.vec.w = 0.0;
	return (vec);
}
