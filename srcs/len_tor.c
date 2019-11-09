/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_tor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:53:57 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/05 14:54:41 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"

double	len_tor(t_vec point, t_vec param)
{
	t_vec q;

	q = new_vec2(vec_len(new_vec2(point.arr[0], point.arr[2]))\
				- param.arr[0], point.arr[1]);
	return (vec_len(q) - param.arr[1]);
}
