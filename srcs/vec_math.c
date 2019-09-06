/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:24:49 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/02 12:24:50 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec4	vec_fabs(t_vec4 vec)
{
	vec.arr[0] = fabs(vec.arr[0]);
	vec.arr[1] = fabs(vec.arr[1]);
	vec.arr[2] = fabs(vec.arr[2]);
	vec.arr[3] = fabs(vec.arr[3]);
	return (vec);
}

t_vec4	vec_fmin(t_vec4 vec, double n)
{
	vec.arr[0] = fmin(vec.arr[0], n);
	vec.arr[1] = fmin(vec.arr[1], n);
	vec.arr[2] = fmin(vec.arr[2], n);
	vec.arr[3] = fmin(vec.arr[3], n);
	return (vec);
}

t_vec4	vec_fmax(t_vec4 vec, double n)
{
	vec.arr[0] = fmax(vec.arr[0], n);
	vec.arr[1] = fmax(vec.arr[1], n);
	vec.arr[2] = fmax(vec.arr[2], n);
	vec.arr[3] = fmax(vec.arr[3], n);
	return (vec);
}
