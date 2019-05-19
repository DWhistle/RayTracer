/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:24:39 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/05/19 18:39:36 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "ft_types.h"

t_vec4	new_vec(ft_decimal val)
{
	t_vec4 vec;

	vec.vec.x = val;
	vec.vec.y = val;
	vec.vec.z = val;
	vec.vec.w = val;
	return (vec);
}

t_vec4	new_vec4(ft_decimal valx, ft_decimal valy, ft_decimal valz,
				ft_decimal valw)
{
	t_vec4 vec;

	vec.vec.x = valx;
	vec.vec.y = valy;
	vec.vec.z = valz;
	vec.vec.w = valw;
	return (vec);
}

t_vec4	new_vec3(ft_decimal valx, ft_decimal valy, ft_decimal valz)
{
	t_vec4 vec;

	vec.vec.x = valx;
	vec.vec.y = valy;
	vec.vec.z = valz;
	vec.vec.w = 0.0;
	return (vec);
}

t_vec4	new_vec2(ft_decimal valx, ft_decimal valy)
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
