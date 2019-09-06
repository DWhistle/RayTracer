/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflaction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:17:23 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/06 15:15:38 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"
#include "libft.h"
#include "light.h"

t_vec			get_ref_vec(t_point_data point_data, t_vec vec)
{
	vec = vec_dotdec(vec, -1);
	vec = vec_sub(vec_dotdec(point_data.norm,
	vec_dotvec(point_data.norm, vec) * 2), vec);
	vec = vec_norm(vec);
	return (vec);
}

t_vec			get_ref_color(t_point_data *points)
{
	int		i;
	t_vec	color_ref;
	t_vec	color;
	double	ref;

	i = 0;
	while (points[i].obj)
		i++;
	points[i - 1].color = get_color_obj(points[i - 1]);
	while (i-- >= 2)
	{
		color_ref = points[i].color;
		ref = points[i - 1].obj->reflection;
		color = get_color_obj(points[i - 1]);
		color = vec_sum(vec_dotdec(color, 1 - ref), vec_dotdec(color_ref, ref));
		points[i - 1].color = color;
	}
	return (points[0].color);
}

t_vec			f(t_point_data *points, int depth_ref)
{
	t_vec			color;

	points[depth_ref + 1].obj = 0;
	if (!points)
		return (new_vec0());
	color = get_ref_color(points);
	free(points);
	return (color);
}

t_point_data	reflection(t_scene *scene, t_vec vec, t_point_data point_data, t_point_data (*raymarch)())
{
	t_point_data	n_point_data;
	t_vec			n_vec;
	
	scene->accuracy.depth_ref--;
	n_vec = get_ref_vec(point_data, vec);
	scene->ignore = point_data.obj;
	n_point_data = ray_render(scene, n_vec, point_data.point, raymarch);
	point_data.ref_color = vec_dotdec(n_point_data.color, point_data.obj->reflection);
	scene->accuracy.depth_ref++;
	scene->ignore = 0;
	return (point_data);
}

t_point_data	refraction(t_scene *scene, t_vec vec, t_point_data point_data, t_point_data (*raymarch)())
{
	t_point_data	n_point_data;
	t_vec			n_vec;
	
	scene->accuracy.depth_ref--;
	n_vec = transparency(vec, point_data);
	n_point_data = raymarch_in_obj(point_data.obj, n_vec, scene->accuracy, point_data.point);
	n_vec = transparency(n_vec, n_point_data);
	scene->ignore = point_data.obj;
	n_point_data = ray_render(scene, n_vec, n_point_data.point, raymarch);
	point_data.refr_color = vec_dotdec(n_point_data.color, point_data.obj->refraction);
	scene->accuracy.depth_ref++;
	scene->ignore = 0;
	return (point_data);
}

t_point_data	transparenc(t_scene *scene, t_vec vec, t_point_data point_data, t_point_data (*raymarch)())
{
	t_point_data	n_point_data;
	
	scene->accuracy.depth_ref--;
	scene->ignore = point_data.obj;
	n_point_data = ray_render(scene, vec, point_data.point, raymarch);
	point_data.tranc_color = vec_dotdec(n_point_data.color, point_data.obj->transparency);
	scene->accuracy.depth_ref++;
	scene->ignore = 0;
	return (point_data);
}

t_point_data	ray_render(t_scene *scene, t_vec vec,\
							t_vec point, t_point_data (*raymarch)())
{
	t_point_data	point_data;
	float				n;
	
	point_data = raymarch(scene, vec, scene->accuracy, point);
	if (point_data.obj)
	{
		point_data.color = get_color_obj(point_data);
		point_data.color = light_math(scene, vec, &point_data);
		if (scene->accuracy.depth_ref)
		{
			if (point_data.obj->reflection)
				point_data = reflection(scene, vec, point_data, raymarching);
			if (point_data.obj->refraction && point_data.obj->type != PLANE)
				point_data = refraction(scene, vec, point_data, raymarching);
			if (point_data.obj->transparency)
				point_data = transparenc(scene, vec, point_data, raymarching);
		}
		n = point_data.obj->transparency + point_data.obj->reflection + point_data.obj->refraction;
		if (n > 1.0)
			n = 1.0;
		point_data.color = vec_sum(vec_dotdec(point_data.color, 1 - n),
								vec_dotdec(point_data.tranc_color, point_data.obj->transparency));
		point_data.color = vec_sum(point_data.color,
								vec_dotdec(point_data.refr_color, point_data.obj->refraction));
		point_data.color = vec_sum(point_data.color,
								vec_dotdec(point_data.ref_color, point_data.obj->reflection));
	}
	return (point_data);
}
