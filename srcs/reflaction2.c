/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflaction2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:14:26 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/08 15:26:12 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"
#include "raymarching.h"
#include "libft.h"
#include "light.h"

t_point_data	transparenc(t_scene *scene, t_vec vec,\
				t_point_data point_data, t_point_data (*raymarch)())
{
	t_point_data	n_point_data;

	scene->accuracy.depth_ref--;
	n_point_data = ray_render(scene, vec, vec_sum(point_data.point,\
	vec_dotdec(vec, scene->accuracy.delta * 100.1)), raymarch);
	point_data.tranc_color = n_point_data.color;
	scene->accuracy.depth_ref++;
	return (point_data);
}

void			ff(t_point_data *point_data, float n)
{
	point_data->color = vec_sum(vec_dotdec(point_data->color, 1 - n),
	vec_dotdec(point_data->tranc_color, point_data->obj->transparency));
	point_data->color = vec_sum(point_data->color,
	vec_dotdec(point_data->refr_color, point_data->obj->tr_refraction));
	point_data->color = vec_sum(point_data->color,
	vec_dotdec(point_data->ref_color, point_data->obj->reflection));
}

t_point_data	ray_render(t_scene *scene, t_vec vec,\
							t_vec point, t_point_data (*raymarch)())
{
	t_point_data	point_data;
	float			n;

	point_data = raymarch(scene, vec, scene->accuracy, point);
	if (point_data.obj)
	{
		point_data.color = get_color_obj(point_data);
		point_data.color = light_math(scene, vec, &point_data);
		if (scene->accuracy.depth_ref)
		{
			if (point_data.obj->reflection)
				point_data = reflection(scene, vec, point_data, raymarching);
			if (point_data.obj->tr_refraction && point_data.obj->type != PLANE)
				point_data = refraction(scene, vec, point_data, raymarching);
			if (point_data.obj->transparency)
				point_data = transparenc(scene, vec, point_data, raymarching);
		}
		n = point_data.obj->transparency + point_data.obj->reflection\
		+ point_data.obj->tr_refraction;
		if (n > 1.0)
			n = 1.0;
		ff(&point_data, n);
	}
	return (point_data);
}
