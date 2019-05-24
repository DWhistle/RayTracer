/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_conus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 20:43:35 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/05/23 20:08:31 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"
#include "objects.h"
#include <math.h>

double len_conus(t_vec point, t_obj conus)
{
	//t_vec		h;
	//t_vec		l;
	//ft_decimal	r;
	//t_conus		*cone;
	(void)point;
	(void)conus;
	((t_cone*)conus.obj)->
	//point = vec_sub(point, ((t_conus*)conus.params)->pos);
	//
	//cone = ((t_conus*)conus.params);
	//h = vec_dotvec(point, cone->direction);
	//h = vec_dotdec(cone->direction, h.vec.x + h.vec.y + h.vec.z);
	//r = (h.vec.x + h.vec.y + h.vec.z) / sin(cone->angle);
	return (0);//sqrt(vec_sqrdist(vec_sum(cone->pos, h))) - r);
}
