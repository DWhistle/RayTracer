/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:11:36 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/26 18:58:40 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raymarching.h"

t_point_data	crate_point_data(t_vec norm,
				t_obj *obj, t_vec point, t_vec color)
{
	t_point_data point_data;

	point_data.norm = norm;
	point_data.obj = obj;
	point_data.point = point;
	point_data.color = color;
	return (point_data);
}

double			get_dist(int neg, t_obj **obj, t_vec point, t_scene *scene)
{
	int		counter;
	double	r;
	double	dist;

	counter = 0;
	dist = scene->accuracy.max_dist + 1;
	while (counter != scene->number_objs)
	{
		if (neg == scene->objs[counter].neg && (!scene->ignore ||\
			scene->objs[counter].ind != scene->ignore->ind))
		{
			r = update_r(scene->objs[counter], point);
			if (r < dist)
			{
				dist = r;
				*obj = scene->objs + counter;
			}
		}
		counter++;
	}
	return (dist);
}

t_point_data	raymarch_in_obj(t_obj *obj, t_vec vec,
							t_accuracy accuracy, t_vec point)
{
	double	r[2];
	double	dist;
	t_vec	new_point;

	dist = 0;
	new_point = point;
	new_point = vec_sum(vec_dotdec(vec, accuracy.delta * 2), point);
	while (accuracy.depth_march-- && dist < accuracy.max_dist)
	{
		r[0] = fabs(update_r(*obj, point));
		if (r[0] < accuracy.delta)
		{
			dist += r[0] * 2;
			new_point = vec_sum(vec_dotdec(vec, dist), point);
			return (crate_point_data(get_normal(new_point, *obj),\
					obj, new_point, new_vec0()));
		}
		dist += r[0];
		new_point = vec_sum(vec_dotdec(vec, dist), point);
	}
	return (crate_point_data(new_vec0(), NULL, new_vec0(), new_vec0()));
}

t_point_data	raymarching(t_scene *objs, t_vec vec,
							t_accuracy accuracy, t_vec point)
{
	double	r[2];
	t_obj	*obj;
	t_obj	*obj2;
	double	dist;
	t_vec	new_point;

	dist = 0;
	obj = 0;
	new_point = point;
	while (accuracy.depth_march-- && dist < accuracy.max_dist)
	{
		r[0] = get_dist(0, &obj, new_point, objs);
		r[1] = get_dist(1, &obj2, new_point, objs);
		r[0] = fmax(r[0], -r[1]);
		if (r[0] + r[1] > 0.001)
			obj2 = obj;
		if (r[0] < accuracy.delta)
		{
			return (crate_point_data(get_normal(new_point, *obj2),\
					obj, new_point, new_vec0()));
		}
		dist += r[0];
		new_point = vec_sum(vec_dotdec(vec, dist), point);
	}
	return (crate_point_data(new_vec0(), NULL, new_vec0(), new_vec0()));
}

t_point_data	shadowmarching(t_scene *objs, t_vec vec,
							t_accuracy accuracy, t_vec point)
{
	double	r[2];
	t_obj	*obj;
	double	dist;
	t_vec	new_point;

	dist = 0;
	obj = 0;
	new_point = point;
	while (accuracy.depth_march-- && dist < accuracy.max_dist)
	{
		r[0] = fabs(get_dist(0, &obj, new_point, objs));
		if (r[0] < accuracy.delta)
		{
			return (crate_point_data(get_normal(new_point, *obj),\
					obj, new_point, new_vec0()));
		}
		dist += r[0];
		new_point = vec_sum(vec_dotdec(vec, dist), point);
	}
	return (crate_point_data(new_vec0(), NULL, new_vec0(), new_vec0()));
}
