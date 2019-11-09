/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_mandelbub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:52:49 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/08 13:03:22 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"

void	len_mandelbub2(t_vec point, t_mandelbub *man)
{
	man->y4 = man->y2 * man->y2;
	man->z = man->w.vec.z;
	man->z2 = man->z * man->z;
	man->z4 = man->z2 * man->z2;
	man->k3 = man->x2 + man->z2;
	man->k2 = 1 / sqrt(man->k3 * man->k3 * man->k3\
	* man->k3 * man->k3 * man->k3 * man->k3);
	man->k1 = man->x4 + man->y4 + man->z4 - 6.0 * man->y2 * man->z2\
	- 6.0 * man->x2 * man->y2 + 2.0 * man->z2 * man->x2;
	man->k4 = man->x2 - man->y2 + man->z2;
	man->w.vec.x = point.vec.x + 64.0 * man->x\
	* man->y * man->z * (man->x2 - man->z2) * man->k4 *\
	(man->x4 - 6.0 * man->x2 * man->z2 + man->z4) * man->k1 * man->k2;
	man->w.vec.y = point.vec.y - 16.0 * man->y2 * man->k3\
	* man->k4 * man->k4 + man->k1 * man->k1;
	man->w.vec.z = point.vec.z - 8.0 * man->y * man->k4 * (man->x4 * man->x4 -\
	28.0 * man->x4 * man->x2 * man->z2 + 70.0 * man->x4 * man->z4\
	- 28.0 * man->x2 * man->z2 * man->z4 + man->z4 * man->z4)\
	* man->k1 * man->k2;
	man->m = vec_dotvec(man->w, man->w);
}

double	len_mandelbub(t_vec point, t_vec param)
{
	t_mandelbub		man;
	int				i;

	man.w = point;
	man.m = vec_dotvec(man.w, man.w);
	man.trap = vec_fabs(man.w);
	man.trap.arr[3] = man.m;
	man.dz = 1.0;
	i = 0;
	while (i < param.arr[0])
	{
		man.m2 = man.m * man.m;
		man.m4 = man.m2 * man.m2;
		man.dz = 8.0 * sqrt(man.m4 * man.m2 * man.m) * man.dz + 1.0;
		man.x = man.w.vec.x;
		man.x2 = man.x * man.x;
		man.x4 = man.x2 * man.x2;
		man.y = man.w.vec.y;
		man.y2 = man.y * man.y;
		len_mandelbub2(point, &man);
		if (man.m > 256.0)
			break ;
		i++;
	}
	return (0.25 * log(man.m) * sqrt(man.m) / man.dz);
}
