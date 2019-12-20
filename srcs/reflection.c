/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:17:23 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/12/20 18:24:23 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"
#include "raymarching.h"
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

t_point_data	reflection(t_scene *scene, t_vec vec,
			t_point_data point_data, int depth_ref)
{
	t_point_data	n_point_data;
	t_vec			n_vec;

	n_vec = get_ref_vec(point_data, vec);
	n_point_data = ray_render(scene, n_vec, vec_sum(point_data.point,\
	vec_dotdec(n_vec, scene->accuracy.delta * 1.1)), depth_ref);
	point_data.ref_color = n_point_data.color;
	scene->ignore = 0;
	return (point_data);
}

t_point_data	refraction(t_scene *scene, t_vec vec,\
				t_point_data point_data, int depth_ref)
{
	t_point_data	n_point_data;
	t_vec			n_vec;

	n_vec = transparency(vec, point_data, point_data.obj->refraction, 1.0);
	n_point_data = ray_render(scene, n_vec, vec_sum(point_data.point,\
	vec_dotdec(n_vec, scene->accuracy.delta * 100.1)), depth_ref);
	point_data.refr_color = n_point_data.color;
	return (point_data);
}
