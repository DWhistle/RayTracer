/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:53:54 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/05 14:54:54 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"

double	len_sphere(t_vec point, t_vec param)
{
	return (vec_len(point) - fabs(param.arr[0]));
}
