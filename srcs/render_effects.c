/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_effects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 12:47:34 by bturcott          #+#    #+#             */
/*   Updated: 2019/09/21 13:20:52 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"
#include "libft.h"
#include "light.h"

t_point_data	reflection(t_scene *scene, t_vec vec,
		t_point_data point_data, t_point_data (*raymarch)())
{
	t_point_data	n_point_data;
	t_vec			n_vec;

	scene->accuracy.depth_ref--;
	n_vec = get_ref_vec(point_data, vec);
	scene->ignore = point_data.obj;
	n_point_data = ray_render(scene, n_vec, point_data.point, raymarch);
	point_data.ref_color = n_point_data.color;
	scene->accuracy.depth_ref++;
	scene->ignore = 0;
	return (point_data);
}

t_point_data	refraction(t_scene *scene, t_vec vec,
		t_point_data point_data, t_point_data (*raymarch)())
{
	t_point_data	n_point_data;
	t_vec			n_vec;

	scene->accuracy.depth_ref--;
	n_vec = transparency(vec, point_data);
	n_point_data = raymarch_in_obj(point_data.obj, n_vec,
			scene->accuracy, point_data.point);
	n_vec = transparency(n_vec, n_point_data);
	scene->ignore = point_data.obj;
	n_point_data = ray_render(scene, n_vec, n_point_data.point, raymarch);
	point_data.refr_color = n_point_data.color;
	scene->accuracy.depth_ref++;
	scene->ignore = 0;
	return (point_data);
}

t_point_data	transparenc(t_scene *scene, t_vec vec,
		t_point_data point_data, t_point_data (*raymarch)())
{
	t_point_data	n_point_data;

	scene->accuracy.depth_ref--;
	scene->ignore = point_data.obj;
	n_point_data = ray_render(scene, vec, point_data.point, raymarch);
	point_data.tranc_color = n_point_data.color;
	scene->accuracy.depth_ref++;
	scene->ignore = 0;
	return (point_data);
}

t_point_data	operate_reflection(t_scene *scene,
		t_vec vec, t_point_data point_data)
{
	if (point_data.obj->reflection)
		point_data = reflection(scene, vec, point_data, raymarching);
	if (point_data.obj->refraction && point_data.obj->type != PLANE)
		point_data = refraction(scene, vec, point_data, raymarching);
	if (point_data.obj->transparency)
		point_data = transparenc(scene, vec, point_data, raymarching);
	return (point_data);
}

t_point_data	operate_color(t_point_data point_data, float n)
{
	point_data.color = vec_sum(vec_dotdec(point_data.color, 1 - n),
			vec_dotdec(point_data.tranc_color, point_data.obj->transparency));
	point_data.color = vec_sum(point_data.color,
			vec_dotdec(point_data.refr_color, point_data.obj->refraction));
	point_data.color = vec_sum(point_data.color,
			vec_dotdec(point_data.ref_color, point_data.obj->reflection));
	return (point_data);
}
