/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflaction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:17:23 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/26 18:58:40 by hgreenfe         ###   ########.fr       */
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

t_point_data	ray_render(t_scene *scene, t_vec vec,\
							t_vec point, t_point_data (*raymarch)())
{
	t_point_data		point_data;
	float				n;

	point_data = raymarch(scene, vec, scene->accuracy, point);
	if (point_data.obj)
	{
		point_data.color = get_color_obj(point_data);
		point_data.color = light_math(scene, vec, &point_data);
		if (scene->accuracy.depth_ref)
			point_data = operate_reflection(scene, vec, point_data);
		n = point_data.obj->transparency + point_data.obj->reflection
		+ point_data.obj->refraction;
		if (n > 1.0)
			n = 1.0;
		point_data = operate_color(point_data, n);
	}
	return (point_data);
}
